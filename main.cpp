#include <iostream>
#include <string>
using namespace std;

int surf_internet(string url) {
  return system(url.insert(0, "start ").c_str());
}

int main() {
  string url;
  cin >> url;
  return surf_internet(url);
}
