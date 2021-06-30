#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXDATASIZE 16384

void *get_in_addr(struct sockaddr *sa);
ssize_t sendall(int sockfd, void *buffer, size_t length);
ssize_t recvall(int sockfd, void *buffer, size_t length);
ssize_t recv_line(int sockfd, char *buf, size_t bufsize);
ssize_t recv_to_fd(int sockfd, int filefd);
