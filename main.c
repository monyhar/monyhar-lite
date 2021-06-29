#include <stdio.h>

#include "log.h"
#include "parser.h"
#include "stream.h"

int main(int argc, char *argv[]) {
  s_uri uri_parsed;
  memset(&uri_parsed, 0, sizeof(s_uri));
  if (argc < 2) {
    L_ERRF("Usage: %s [OPTIONS] URL\n", argv[0]);
    return 0;
  }
  if (argc > 2) {
    // where we'll parse options
    for (int i = 1; i < argc - 1; i++) {
      if (strstr(argv[i], "-v") == argv[i]) slow_loglevel(DBG);
    }
  }
  if (parse_uri(argv[argc - 1], &uri_parsed)) {
    L_ERRF("Fatal error when parsing URL: %s", argv[argc - 1]);
    return 1;
  }

  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((rv = getaddrinfo(uri_parsed.hostname, uri_parsed.port, &hints,
                        &servinfo)) != 0) {
    L_ERRF("getaddrinfo: %s", gai_strerror(rv));
    return 1;
  }
  int sockfd;
  // loop through all the results and connect to the first we can
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      L_PERROR();
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      L_PERROR();
      continue;
    }

    break;
  }

  if (p == NULL) {
    L_ERR("failed to connect.\n");
    return 2;
  }

  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s,
            sizeof s);
  L_DEBUGF("connecting to %s...", s);

  freeaddrinfo(servinfo);  // all done with this structure

  char *buf = calloc(MAXDATASIZE, 1);
  if (!buf) {
    L_PERROR();
    exit(1);
  }
  snprintf(buf, MAXDATASIZE,
           "GET %s HTTP/1.1\r\n"
           "Host: %s:%s\r\n"
           "Connection: close\r\n"
           "Accept: */*\r\n"
           "User-Agent: monyhar-greasy/0.1 (like curl/7.72.0)\r\n\r\n",
           uri_parsed.path, uri_parsed.hostname, uri_parsed.port);
  if (sendall(sockfd, buf, strlen(buf)) < 0) {
    L_ERR("Error occured when sending HTTP Request.");
    exit(1);
  }
  free(buf);
  buf = NULL;
  ssize_t content_size = recv_to_fd(sockfd, STDOUT_FILENO);
  if (content_size > 0) {
    L_INFOF("Successfully received %ld byte(s) of payload. Bye.", content_size);
  } else if (content_size < 0) {
    L_ERR("Error when handling HTTP Response.");
  }
  close(sockfd);
  return 0;
}
