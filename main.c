#include <stdio.h>
#include <stdlib.h>

int surf_internet(char *url) {
  char target[512];
  int spf_r = 0;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  spf_r = sprintf(target, "start %s", url);
#elif defined(__linux__)
  spf_r = sprintf(target, "xdg-open %s", url);
#elif defined(__APPLE__)
  spf_r = sprintf(target, "open %s", url);
#else
  return -1;
#endif
  if (spf_r < 0) {
    return -1;
  }
  if (system(target) < 0) {
    return -1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: ./monyhar-lite [URL]\n");
    return EXIT_FAILURE;
  }
  if (surf_internet(argv[1]) < 0) {
    fprintf(stderr, "[monyhar-lite] failed to open your url.\n");
    fprintf(stderr,
            "It's not working because you're not working hard enough.\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
