#include<windows.h>
#include<string.h>
#include<iostream>
int surf_internet(std::string url){
  system(url.c_str());
}
int main() {
  std::string o;
  std::cin>>o;
  surf_internet("start http://"+o);
}

