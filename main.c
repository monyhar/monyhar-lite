#include <stdio.h> // printf,scanf 原型
#include <stdlib.h> // malloc,free 原型
#include <string.h> //strcat原型
int surf_internet() {
  while(1){
    printf("URL:");
    char * url = malloc(sizeof(char) * 1024); //1024个字符的url，应该够用了
    if (scanf("%s",&url)){
      //读取
      char * command = malloc(sizeof(char) * 1029);
      *command = "curl ";
      strcat(command,url);//拼接
      system(command);//命令行调用
      free(command); //释放内存
      printf("\n");
      
    };
    free(url);
  return 0;
}

int main() {
  return surf_internet();
}
