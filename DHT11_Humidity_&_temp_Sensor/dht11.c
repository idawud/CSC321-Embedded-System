#include <stdio.h>
#include <stdlib.h>
#include <dht11.h>

int main(){
  dht11Init();
  dht11SetDebug(true);
  printf("Reading Data: \n");
  dht11Measurement();
  
  return 0;
}
