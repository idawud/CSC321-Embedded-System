#include <stdio.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define RTC 0x68
#define SECONDS 0
#define MINUTES 1
#define HOURS   2
#define DAY     3
#define DATE    4
#define MONTH   5
#define YEAR    6

typedef char *dayOfWeek_t;
typedef char *month_t;
typedef char *monthShort_t;

dayOfWeek_t dayOfWeek[] = {"mon","tue","wed","thu","fri","sat","sun"};
month_t monthName[] = {"jan","feb","mar","apr","may","jun",
		       "jul","aug","sep","oct","nov","dec"};
int monthLength[] = {31,29,31,30,31,30,31,31,30,31,30,31};

static struct option long_options [] =
  {
    {"help",      no_argument,          NULL, '?'},     
    {"seconds",   required_argument,    NULL, 's'},      
    {"minutes",   required_argument,    NULL, 'm'},
    {"hours",     required_argument,    NULL, 'h'},      
    {"weekday",   required_argument,    NULL, 'w'},      
    {"date",      required_argument,    NULL, 'D'},      
    {"month",     required_argument,    NULL, 'M'},
    {"year",      required_argument,    NULL, 'Y'},
    {NULL,0,NULL,0}
  };

void printUsage()
{
  printf("The rtc program, called without parameters, will print the\n");
  printf("current date and time\n");
  printf("If called with arguments it will set the realtime clock\n");
  printf("arguments are:\n");
  printf("   long argument, short argument, value\n");
  printf("   --help,        ?               n/a\n");
  printf("   --seconds      -s              0..59\n");
  printf("   --minutes      -m              0..59\n");
  printf("   --weekday      -w              1..7\n");
  printf("                                  or \"mon\",\"tue\",\"wed\"...\n");
  printf("   --date         -D              date within month\n");
  printf("   --month        -M              1..12\n");
  printf("                                  or \"jan\",\"feb\",\"mar\"...\n");
  printf("   --year         -Y              0..99\n");
  }

int main(int argc, char *argv[]) {

  int i,fd;
  int seconds,minutes,hours,day,date,month,year;
  int retCode;
  int option,optIndex=0;
  char *optargPtr,weekday[4],monthNm[4];
  int currentDate,currentMonth,currentYear;
  int data=0;
  
  if ((fd=wiringPiI2CSetup(RTC)) < 0) {
    printf("Cannot setup I2C\n");
    perror("Error is:");
    return -1;
  }
  /*
    if no arguments are given, just print the current date and time 
  */
  if (argc == 1) {
    seconds = wiringPiI2CReadReg8(fd,SECONDS);
    minutes = wiringPiI2CReadReg8(fd,MINUTES);
    hours   = wiringPiI2CReadReg8(fd,HOURS);
    day     = wiringPiI2CReadReg8(fd,DAY);
    date    = wiringPiI2CReadReg8(fd,DATE);
    month   = wiringPiI2CReadReg8(fd,MONTH);
    year    = wiringPiI2CReadReg8(fd,YEAR);
    
    printf("Read from RTC:\n");
    printf("Time: %02x:%02x:%02x\n",hours, minutes, seconds);
    strcpy(weekday,dayOfWeek[day-1]);
    weekday[0]=toupper(weekday[0]);

    /* convert month from bcd to decimal */
    month = (month >> 4) *10 + month & 0xf;
    strcpy(monthNm,monthName[month-1]);
    monthNm[0] = toupper(monthNm[0]);
    printf("Date: %s %x. %s 20%02x\n",weekday, date, monthNm, year);
    return 1;
  }
  /* here if there are arguments */

  if (!strcmp(argv[1],"?")) {
    printUsage();
    return 1;
  }
  while (true) {
    option= getopt_long (argc, argv, "?s:m:h:w:D:M:Y:",
			 long_options, &optIndex);
    
    if (option == -1)
      break;
    switch (option) {
      /* Here for seconds */
    case 's':
      /* 
	 first read the argument for sedondes in decimal and check
	 that the value is between 0 and 59
	 if this is the case, then read it in hex to get the the value in bcd
	 It works in a similar fashion for the other arguments
      */
      printf("Seconds: %s\n",optarg);
      if (sscanf(optarg,"%d",&seconds) < 0) {
	printf("Invalid value for seconds: %s, not written to rtc\n",optarg);
	break;
      }
      if ((seconds < 0) || (seconds > 59)) {
	printf("Invalid value for seconds: %s, not written to rtc\n",optarg);
	break;
      }
      sscanf(optarg,"%x",&seconds);
      wiringPiI2CWriteReg8(fd,SECONDS,seconds);
      break;
      
      /* Here for minutes */      
    case 'm':
      printf("Minutes: %s\n",optarg);
      if (sscanf(optarg,"%d",&minutes) < 0) {
	printf("Invalid value for minutes: %s, not written to rtc\n",optarg);
	break;
      }
      if ((minutes < 0) || (minutes > 59)) {
	printf("Invalid value for minutes: %s, not written to rtc\n",optarg);
	break;
      }
      sscanf(optarg,"%x",&minutes);
      wiringPiI2CWriteReg8(fd,MINUTES,minutes);
      break;
      
      /* Here for hours */      
    case 'h':
      printf("Hours: %s\n",optarg);
      if (sscanf(optarg,"%d",&hours) < 0) {
	printf("Invalid value for hours: %s, not written to rtc\n",optarg);
	break;
      }
      if ((hours < 0) || (hours > 23)) {
	printf("Invalid value for hours: %s, not written to rtc\n",optarg);
	break;
      }      
      sscanf(optarg,"%x",&hours);      
      printf("Writing hour: %d to the rtc\n",hours);
      wiringPiI2CWriteReg8(fd,HOURS,hours);
      break;

    case 'w':
      for (i=0;i<7;i++) {
	/* convert optarg to lower case */
	optargPtr = optarg;
	for(; *optargPtr; ++optargPtr) *optargPtr = tolower(*optargPtr);
	if (!strcmp(dayOfWeek[i],optarg)) {
	  printf("day of the week is %s, %d\n",optarg,i+1);
	  wiringPiI2CWriteReg8(fd,DAY,i+1);
	  goto weekdayDone;
	}
      }
      /* optarg may also be 1 .. 7 */
      if (sscanf(optarg,"%d",&i) < 0) {	  
 	printf("Invalid value for day of the week: %s, not written to rtc\n",optarg);
	goto weekdayDone;
      }
      if((i<1) || (i>7)) {
	printf("Invalid value for day of the week: %s, not written to rtc\n",optarg);
	goto weekdayDone;
      }
      printf("Writing weekday: %s corresponding to day %d to the rtc\n",dayOfWeek[i-1],i);
      wiringPiI2CWriteReg8(fd,DAY,i);
    weekdayDone:
      break;
      
      /* here for month */
    case 'M':
      /* check optarg against day and year */
      currentDate     = wiringPiI2CReadReg8(fd,DATE);
      currentYear    = wiringPiI2CReadReg8(fd,YEAR);
      /* convert from BCD to binary */
      currentDate = (currentDate >> 4)*10 + (currentDate & 0xf);
      currentYear = (currentYear >> 4)*10 + (currentYear & 0xf);
      
      for (i=0;i<12;i++) {
	/* convert optarg to lower case */
	optargPtr = optarg;
	for(; *optargPtr; ++optargPtr) *optargPtr = tolower(*optargPtr);
	if (!strcmp(monthName[i],optarg)) {
	  month = ((i+1)/10)*16 + (i+1)%10;
	  printf("month is %s, %x\n",optarg,month);
	  wiringPiI2CWriteReg8(fd,MONTH,month);
	  goto monthDone;
	}
      }

      /* optarg may also be 1 .. 12 */
      if (sscanf(optarg,"%d",&i) < 0) {	  
 	printf("Invalid value for month: %s, not written to rtc\n",optarg);
	goto monthDone;
      }
      if((i<1) || (i>12)) {
	printf("Invalid value for month: %s, not written to rtc\n",optarg);
	goto monthDone;
      }
      /* check if currentDate exists in this month */
      if (currentDate > monthLength[i-1]) {
	strcpy(monthNm,monthName[i-1]);
	monthNm[0]=toupper(monthNm[0]);
	printf("There is no day %d in %s\n",currentDate,monthNm);
	printf("Month not written to rtc, please change day first\n");
	goto monthDone;
      }
      /* check for leap year */
      if ((i==1) && (currentDate==29) && (currentYear%4)) {
        printf("Day is 29. February but year: 20%02d is not a leap year\n",currentYear);
	printf("Month not written to rtc, please change day first\n");
	goto monthDone;	
      }
	
      sscanf(optarg,"%x",&i);
      printf("Writing month: %x to the rtc\n",i);
      wiringPiI2CWriteReg8(fd,MONTH,i);
      
    monthDone:
      break;     

    case 'D':
      /* check optarg against month and year */
      currentMonth   = wiringPiI2CReadReg8(fd,MONTH);
      currentYear    = wiringPiI2CReadReg8(fd,YEAR);
      /* convert currentMonth from BCD to binary */
      currentMonth = (currentMonth >> 4)*10 + (currentMonth & 0xf);
      currentYear  = (currentYear  >> 4)*10 + (currentYear  & 0xf);
      
      if (sscanf(optarg,"%d",&i) < 0) {	  
 	printf("Invalid value for day: %s, not written to rtc\n",optarg);
	goto dayDone;
      }
      if((i<1) || (i>monthLength[currentMonth])) {
	printf("Invalid value for day: %s, not written to rtc\n",optarg);
	goto dayDone;
      }
      else {
	/* check for leap year */
	if ((currentMonth == 2) && (i == 29) && (currentYear % 4)) {
	  printf("Day is 29. February but year: 20%02d is not a leap year\n",currentYear);
	  printf("Day value is not written to rtc\n");
	  goto dayDone;
	}
      }
      sscanf(optarg,"%x",&i);
      printf("Writing date: %x to the rtc\n",i);
      wiringPiI2CWriteReg8(fd,DATE,i);
      
    dayDone:
      break;
      
      /* here for year */
    case 'Y':
      currentMonth  = wiringPiI2CReadReg8(fd,MONTH);
      currentDate    = wiringPiI2CReadReg8(fd,DATE);

      /* convert from BCD to binary */
      currentMonth = (currentMonth >>4)*10 + (currentMonth&0xf);
      currentDate  = (currentDate  >>4)*10 + (currentDate&0xf);

      printf("year: %s\n",optarg);
      if (sscanf(optarg,"%d",&i) < 0) {	  
 	printf("Invalid value for year: %s, not written to rtc\n",optarg);
	goto yearDone;
      }
      if((i<0) || (i>99)) {
 	printf("Invalid value for year: %s, not written to rtc\n",optarg);
	goto yearDone;
      }
      /* check for leap year */
      if ((currentMonth==2) && (currentDate==29) && (i%4)) {
        printf("Day is 29. February but year: 20%02d is not a leap year\n",i);
	printf("Year not written to rtc, please change day or month first\n");
	goto monthDone;	
      }
	

      sscanf(optarg,"%x",&i);
      printf("Writing year: %02x to rtc\n",i); 
      wiringPiI2CWriteReg8(fd,YEAR,i);
    yearDone:
    break;
      
    case '?':
    default:
      printUsage();
      break;      
    }
    return 0;
  }
}
