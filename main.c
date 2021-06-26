#include <stdio.h>
#include <unistd.h>


int surf_internet() {
  return 0;
}

int oneBillionAfterTheDecimalPointOfPi() {
  sleep(1);
  return 3;
}

int main() {
  printf("π小数点后10亿位是%d", oneBillionAfterTheDecimalPointOfPi());
  return surf_internet();
}
