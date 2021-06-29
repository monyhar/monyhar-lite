#include "stream.h"

#include "log.h"

void *get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

ssize_t sendall(int sockfd, void *buffer, size_t length) {
  size_t sent = 0;
  ssize_t ret;
  do {
    ret = send(sockfd, buffer + sent, length - sent, 0);
    if (ret > 0) {
      sent += ret;
    } else {
      if (errno == EINTR)
        continue;
      else {
        L_PERROR();
        return -1;
      }
    }
  } while (sent < length);
  return sent;
}

ssize_t recvall(int sockfd, void *buffer, size_t length) {
  size_t recved = 0;
  ssize_t ret;
  do {
    ret = recv(sockfd, buffer + recved, length - recved, 0);
    if (ret > 0) {
      recved += ret;
    } else if (ret == 0) {
      break;
    } else {
      if (errno == EINTR) {
        ret = 0;
        continue;
      } else {
        L_PERROR();
        return -1;
      }
    }
  } while (recved < length);
  return recved;
}

ssize_t recv_line(int sockfd, char *buf, size_t bufsize) {
  char *ptr = buf;
  ssize_t ret = 0;
  do {
    ptr += ret;
    if (ptr - buf > (ssize_t)bufsize) return -1;
    ret = recv(sockfd, ptr, 1, 0);
    if (ret < 0) {
      if (errno == EINTR) {
        ret = 0;
        continue;
      } else {
        L_PERROR();
        return -1;
      }
    }
  } while (!strstr(buf, "\r\n"));
  return (ptr - buf) + ret;
}

ssize_t recv_to_fd(int sockfd, int filefd) {
  ssize_t recv_size = 0, claimed_size = 0;
  char *buf = calloc(MAXDATASIZE, 1);
  if (!buf) {
    L_PERROR();
    return -1;
  }
  char *ptr = buf;

  // read http status line
  ssize_t ret = recv_line(sockfd, buf, MAXDATASIZE);
  if (ret < 0) {
    free(buf);
    return -1;
  }
  char *spliter;
  if ((spliter = strchr(buf, ' '))) {
    if (strcasestr(spliter, "200 OK")) {
      L_INFO("Server responsed: 200 OK...");
      ptr += ret;
    } else {
      char tmp[100];
      memset(tmp, 0, 100);
      int r_code_len = strchr(spliter, '\r') - spliter - 1;
      strncpy(tmp, spliter + 1, r_code_len > 99 ? 99 : r_code_len);
      L_INFOF("Server responsed: %s", tmp);
      free(buf);
      return 0;
    }
    ret = 0;
    while (!strstr(ptr - 2, "\r\n\r\n")) {
      ptr += ret;
      ret = recv_line(sockfd, ptr, MAXDATASIZE - (buf - ptr));
      if (ret < 0) {
        free(buf);
        return -1;
      }
      if (strcasestr(ptr, "Content-Length:")) {
        claimed_size = strtol(ptr + strlen("Content-Length:"), NULL, 10);
        L_INFOF("Header claimed content size of %ld bytes.", claimed_size);
      }
    }
    ptr += ret;
    L_DEBUGF("Header Length: %ld bytes", (ptr - buf));

    if (filefd < 0) {
      L_PERROR();
      free(buf);
      return -1;
    }
    L_DEBUGF("output opened at fd=%d", filefd);
    memset(buf, 0, (ptr - buf) + 1);
    while ((ret = recv(sockfd, buf, MAXDATASIZE, 0))) {
      if (ret < 0) {
        if (errno == EINTR) {
          ret = 0;
          continue;
        } else {
          L_PERROR();
          close(filefd);
          free(buf);
          return -1;
        }
      }
      recv_size += ret;
      ssize_t wr_ret = 0, written_size = 0;
      while (written_size < ret) {
        wr_ret = write(filefd, buf, ret - written_size);
        if (wr_ret < 0) {
          if (errno == EINTR) {
            wr_ret = 0;
            continue;
          } else {
            L_PERROR();
            close(filefd);
            free(buf);
            return -1;
          }
        }
        written_size += wr_ret;
        L_DEBUGF("Received %ld bytes and written to output", wr_ret);
        L_INFOF("Received %ld bytes in total", recv_size);
      }
    }
    if (fdatasync(filefd)) {
      L_DEBUG("I/O operations may not be sync'd yet.");
    }

    close(filefd);

    if (claimed_size != recv_size) {
      L_WARNF("claimed %ld byte(s), written %ld byte(s)", claimed_size,
              recv_size);
    }
  } else {
    L_ERR("Invalid HTTP Response.\n");
    free(buf);
    return -1;
  }
  free(buf);
  return recv_size;
}
