#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>
#define LED 0

void blinkExit(int dummy){
  printf("Blink: cleaning up \n");
  digitalWrite(LED,LOW);
   exit(0);
}

int main (void){
  printf("RaspberryPi Blink \n");
  signal(SIGINT,blinkExit);
  wiringPiSetup () ;
  pinMode (LED, OUTPUT) ;
  for (;;)
  {
    digitalWrite (LED, HIGH) ;
    delay (500) ;
    digitalWrite (LED,  LOW) ;
    delay (500) ;
  }
  return 0 ;
}
