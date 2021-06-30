#include "log.h"
#define PROTO_MAXLEN 10
#define URL_MAXLEN 6144
#define HOSTNAME_MAXLEN 255

typedef struct {
  char *proto;
  char *hostname;
  char *port;
  char *path;
} s_uri;

int parse_uri(char *str, s_uri *res);
