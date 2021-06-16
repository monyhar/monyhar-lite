#include <stdio.h>
#include <windows.h>

int surf_internet() {
  return 0;
}

void xiaomi_internet(){
  printf("兼容小米平台,30秒后启动，<点击跳过广告>");
}

int main() {
  xiaomi_internet();
  Sleep(3000);
  return surf_internet();
}
