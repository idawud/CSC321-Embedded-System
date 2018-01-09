#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <signal.h>


int main (int argc, char **argv){
  char read[]="read";
  char write[]="write";
  printf("RaspberryPi ON/OFF \n");

  
  wiringPiSetup () ;

  if(!(argc==3 || argc==4)){
    printf("Usage: %s",argv[0]);
    exit(0);
  }

  if((!strcmp(read,argv[1])) || (!strcmp(write,argv[1])) ) {

	 if(!strcmp(read,argv[1])){
	int pin= atoi(argv[2]);
	if(pin>=0 && pin<=7){
	 int state= digitalRead(pin);
	 printf("%d \n",state);
	}
	if(pin<0 || pin>7){
	   printf("Invalid gpio PIN\n");}
       }


      if(!strcmp(write,argv[1])){
	int pin=atoi(argv[2]);
	int val=atoi(argv[3]);
	if((pin>=0 || pin<=7)&&(val==0 || val==1)){
	  digitalWrite(pin,val);
	}
	if(pin<0 || pin>7){
       printf("Invalid gpio PIN\n");}
    
    if(!(val==0 || val==1)){
    printf("Invalid gpio Value\n");
    }
   
  }
  }
     else{ printf("Invalid Command \n");}


      return 0;
      }
