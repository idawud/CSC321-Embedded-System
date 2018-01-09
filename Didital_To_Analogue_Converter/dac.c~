    #include <stdio.h>
    #include <stdlib.h>
    #include <pigpioErr.h>
    #include <pigpiod_if2.h>
   

    #define I2C_BUS 1
    #define MCP4725_ADDRESS 0x62
    #define I2C_FLAGS 0
    #define OK 0

    int main(int argc, char **argv){
      int retcode,pi,handle;
      unsigned char reg,value;
      short int dacValue;

      //check if DAC value has been passed
       if(argc != 2){
      printf("DAC: invalid argument list, pass a value to after %s \n",argv[0]);
      return -1;
       }
       
      //connection to pigpiod_i2f library & checking for daemon provision
     if( (retcode=pigpio_start(NULL,NULL)) <0) {
	printf("DAC: Could not open connection to pigiod \n");
	printf("retcode: %d",retcode);
	printPigpioErr(retcode);

	if((pigifError_t)retcode == pigif_bad_connect){
	printf("Pigiod Daemon no started\n");
	}
	return -1;
     }
     else
       pi=retcode;
     //connection to i2c device

    if((retcode=i2c_open(pi,I2C_BUS,MCP4725_ADDRESS,I2C_FLAGS)) < 0){
    printf("DAC: cannot open I2C_BUS %d at address %0x20 \n",I2C_BUS,MCP4725_ADDRESS);
    pigpioPrintI2CError(retcode);
    return -1;
    }
    // connection successful
    //if(mcp4725Debug){
     printf("DAC: pigpio Started successfully \n ");
    //}

    handle=retcode;
    //writing the DAC value passed at command line
    if(((argv[1])[0])=="a" &&((argv[1])[0])=="f"){
      dacValue = strtol(argv[1],NULL,16);
    }
    else if((argv[1])[0]=="x" || (argv[1])[0]=="X"){
      dacValue = strtol(argv[1],NULL,16);
    }
    else if(((argv[1])[0])=="0" ){
      dacValue = atoi(argv[1]);
    }
    else{
      printf("DAC: Invalid Argument Value \n");
    }
      reg= dacValue >> 8;
      value = dacValue & 0xff;
      retcode=i2c_write_byte_data(pi,handle,reg,value);
      if(retcode !=OK){
	printf("DAC: could not write to dacregister errcode=%d\n",retcode);
	pigpioPrintI2CError(retcode);
	return -1;
      }
      else{
	printf("DAC: the value %d has been sent to the dac \n" ,dacValue);
      }
    
    
      return 0;
    }

