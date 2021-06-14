#include <stdio.h>
#include <string.h>

// sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int surf_internet(const char *url) {
  printf("\n加载中.");

  if (strcmp(url, "https://www.monyhar.com/lite") == 0) {
    printf("\n\n梦弘浏览器 自主研发版本 - 完全自主研发，打破国外垄断，比 Chrome 快 600%%。\n\n");
    return 0;
  }

  for (int i = 0; i < 9; ++i) {
    printf(".");
    fflush(stdout);
#ifdef _WIN32
    Sleep(500);
#else
    usleep(500000);
#endif
  }

  printf("\n\n连接超时\n\n"
      "%s 的服务器响应时间过长。\n"
      "- 此站点暂时无法使用或者太过忙碌。请过几分钟后再试。\n"
      "- 如果您无法载入任何网页，请检查您计算机的网络连接状态。\n"
      "- 如果您的计算机或网络受到防火墙或者代理服务器的保护，请确认 monyhar-lite 已被授权访问网络。\n\n"
      , url);
  return 1;
}

int main() {
  char url[10000];
  while (printf("请输入网址: ") && ~scanf("%s", url)) {
    surf_internet(url);
  }
  return 0;
}
