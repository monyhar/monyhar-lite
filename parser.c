#include "parser.h"

#include <ctype.h>
#include <string.h>
#define larger(X, Y) (X > Y ? X : Y)
#define smaller(X, Y) (X < Y ? X : Y)

int parse_uri(char *str, s_uri *res) {
  char *pos = strstr(str, "://");
  // assumes http by if protocol header not found
  res->proto =
      pos ? strndup(str, smaller((pos - str), PROTO_MAXLEN)) : strdup("http");
  pos = pos ? pos + 3 : str;
  for (int i = strlen(res->proto) - 1; i >= 0; i--) {
    res->proto[i] = tolower(res->proto[i]);
  }
  int host_len;
  if ((host_len = strchr(pos, ':') - pos) < HOSTNAME_MAXLEN && host_len > 0) {
    res->hostname = strndup(pos, smaller(host_len, HOSTNAME_MAXLEN));
    pos += host_len + 1;
    char *port_ends_at;
    if ((port_ends_at = strchr(pos, '/'))) {
      if (port_ends_at - pos < 10) {
        res->port = strndup(pos, port_ends_at - pos);
      } else {
        L_ERR("Invalid port: too long.");
      }
    } else {
      if (strlen(pos) < 10) {
        res->port = strndup(pos, 9);
      } else {
        L_ERR("Invalid URL");
      }
    }
  } else {
    res->port = strchr(res->proto, 's') ? strdup("443") : strdup("80");
    if ((host_len = strchr(pos, '/') - pos) < HOSTNAME_MAXLEN && host_len > 0) {
      res->hostname = strndup(pos, host_len);
    } else if ((host_len = strlen(pos)) < HOSTNAME_MAXLEN) {
      res->hostname = strndup(pos, host_len);
    } else {
      L_ERR("Invalid URL");
      return 1;
    }
  }

  res->path =
      strchr(pos, '/') ? strndup(strchr(pos, '/'), URL_MAXLEN) : strdup("/");
  return 0;
}
