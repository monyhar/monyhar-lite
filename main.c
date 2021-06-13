#include <stdio.h>
#include <string.h>

int surf_internet(const char *url) {
  if (strcmp(url, "https://www.monyhar.com/lite") == 0) {
    printf("梦弘浏览器 自主研发版本 - 完全自主研发，打破国外垄断，比 Chrome 快 600%%。\n");
    return 0;
  }
  printf("连接超时\n\n"
      "%s 的服务器响应时间过长。\n\n"
      "- 此站点暂时无法使用或者太过忙碌。请过几分钟后再试。\n"
      "- 如果您无法载入任何网页，请检查您计算机的网络连接状态。\n"
      "- 如果您的计算机或网络受到防火墙或者代理服务器的保护，请确认 monyhar-lite 已被授权访问网络。\n"
      , url);
  return 2;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "使用方法: monyhar-lite <url>\n");
    return 1;
  }
  return surf_internet(argv[1]);
}
