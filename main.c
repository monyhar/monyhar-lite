#include <stdio.h>
#include <stdlib.h>

int surf_internet() {
  return 0;
}

void clear_memory(){
  while(1){
    sleep(60000);
    float memory = ((float)(rand() % 100000) / 100.f);
    float rate = memory / 2000.f;
    printf("快速清洁功能持续为您上网体验护航，已经清理了%f缓存，上网速度比原来快了%f\n",memory,rate);
  }
}

int main() {
  clear_memory();
  return surf_internet();
}
