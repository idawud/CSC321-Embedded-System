#include <stdio.h>
#include <wiringPiI2C.h>
#include <errno.h>

#define RTC 0x68
#define SECONDS 0
#define MINUTES 1
#define HOURS   2
#define DAY     3
#define DATE    4
#define MONTH   5
#define YEAR    6

int setRTC(int fd) {
   int seconds,minutes,hours,day,date,month,year;
   seconds=0;
   minutes=0x03;
   hours=0x23;
   day=6;
   date=0x22;
   month=0x12;
   year=0x17;
   
   wiringPiI2CWriteReg8(fd,SECONDS,seconds);
   wiringPiI2CWriteReg8(fd,MINUTES,minutes);
   wiringPiI2CWriteReg8(fd,HOURS,hours);
   wiringPiI2CWriteReg8(fd,DAY,day);
   wiringPiI2CWriteReg8(fd,DATE,date);
   wiringPiI2CWriteReg8(fd,MONTH,month);
   wiringPiI2CWriteReg8(fd,YEAR,year);  
}
  
int main(int argc, char **argv) {

  int fd;
  int seconds,minutes,hours,day,date,month,year;
  int retCode;
  int data=0;
  
  if ((fd=wiringPiI2CSetup(RTC)) < 0) {
    printf("Cannot setup I2C\n");
    perror("Error is:");
    return -1;
  }
  //  setRTC(fd);

  seconds = wiringPiI2CReadReg8(fd,SECONDS);
  minutes = wiringPiI2CReadReg8(fd,MINUTES);
  hours   = wiringPiI2CReadReg8(fd,HOURS);
  day = wiringPiI2CReadReg8(fd,DAY);
  date = wiringPiI2CReadReg8(fd,DATE);
  month   = wiringPiI2CReadReg8(fd,MONTH);
  year   = wiringPiI2CReadReg8(fd,YEAR);

  printf("Read from RTC:\n");
  printf("hours: 0x%x, minutes: 0x%x, seconds: 0x%x\n",hours, minutes, seconds);
  printf("date: 0x%x, month: 0x%x, year: 0x%x\n",date, month, year);

  wiringPiI2CWriteReg8(fd,0x08,0xaa);
  data=wiringPiI2CReadReg8(fd,0x08);
  printf("data read: %x\n",data);
  return 0;
}
