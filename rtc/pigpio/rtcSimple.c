#include <stdio.h>
#include <stdlib.h>
#include <pigpiod_if2.h>

#define RTC            0x68
#define I2C_BUS        1
#define I2C_FLAGS      0

#define SECONDS 0
#define MINUTES 1
#define HOURS   2
#define DAY     3
#define DATE    4
#define MONTH   5
#define YEAR    6

int pi,i2cHandle;

int setRTC(int fd) {
   int seconds,minutes,hours,day,date,month,year;
   seconds=0;
   minutes=0x03;
   hours=0x23;
   day=6;
   date=0x22;
   month=0x12;
   year=0x17;
   
   i2c_write_byte_data(pi,i2cHandle,SECONDS,seconds);
   i2c_write_byte_data(pi,i2cHandle,MINUTES,minutes);
   i2c_write_byte_data(pi,i2cHandle,HOURS,hours);
   i2c_write_byte_data(pi,i2cHandle,DAY,day);
   i2c_write_byte_data(pi,i2cHandle,DATE,date);
   i2c_write_byte_data(pi,i2cHandle,MONTH,month);
   i2c_write_byte_data(pi,i2cHandle,YEAR,year);
   return 0;
}
  
int main(int argc, char **argv) {

     int retCode;
     int seconds,minutes,hours,day,date,month,year;
     int data=0;
     
     if ((retCode = pigpio_start(NULL,NULL)) < 0) {
       printf("rtcSimple: Cannot initialize pigpio\n");
       return -1;
     }
     else
       pi=retCode;

     printf("rtcSimple: pigpio successfully initialized\n");
     
     if ((retCode = i2c_open(pi,I2C_BUS,RTC,I2C_FLAGS)) < 0) {
       printf("rtcSimple: Cannot open I2C bus %d at address %02x\n",
	      I2C_BUS,RTC);
       return -1;
     }
     else
       i2cHandle=retCode;

     seconds = i2c_read_byte_data(pi,i2cHandle,SECONDS);
     minutes = i2c_read_byte_data(pi,i2cHandle,MINUTES);
     hours   = i2c_read_byte_data(pi,i2cHandle,HOURS);
     day     = i2c_read_byte_data(pi,i2cHandle,DAY);
     date    = i2c_read_byte_data(pi,i2cHandle,DATE);
     month   = i2c_read_byte_data(pi,i2cHandle,MONTH);
     year    = i2c_read_byte_data(pi,i2cHandle,YEAR);
     
     printf("Read from RTC:\n");
     printf("hours: 0x%x, minutes: 0x%x, seconds: 0x%x\n",hours, minutes, seconds);
     printf("day: 0x%x, date: 0x%x, month: 0x%x, year: 0x%x\n",day, date, month, year);
     
     i2c_write_byte_data(pi,i2cHandle,0x08,0xaa);
     data = i2c_read_byte_data(pi,i2cHandle,0x08);

     printf("data read: %x\n",data);
     i2c_close(pi,i2cHandle);
     pigpio_stop(pi);  
     
     return 0;
}
