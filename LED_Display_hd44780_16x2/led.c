//LED Display program for hd44780 16x2 screen
//#include <pigpioErr.h>

#include <stdio.h>
#include <hd44780.h>
#include <pigpiod_if2.h>
#include <stdlib.h>


int main(){
  char *name;
  name = malloc(50);
  if(hd44780Open()<0){
    printf("LED Usage: Error connecting to the LED Dispaly \n");
    return -1;
  }
  else{
    printf("Connection to LED Display successful!\n");
   }
  hd44780Clear();
  
  printf("Please type in your name: ");
  scanf("%s",name);
   
  hd44780PutS("DCSIT Welcomes ");
  hd44780SecondLine();
  hd44780PutS(name);

  hd44780Close();
  return 0;
}
