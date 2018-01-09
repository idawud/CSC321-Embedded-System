#include <stdio.h>
#include <stdlib.h>
#include <dht11.h>

int main(int argc, char **argv){
   FILE *fp;
   int data[DHT11_PROTOCOL_SIZE];
   dht11Init();
   dht11SetDebug(true);
   dht11Measurement();
   if( (fp=fopen("temp.txt", "w+"))== NULL){
     printf("File not found!");
     exit(-1);
   }
   if (dht11GetValidRawData(data) < 0)
     printf("Error when reading data\n");
   for (int i=0;i<DHT11_PROTOCOL_SIZE;i++)
     fprintf(fp,"%d\n",data[i]);
   
   fclose(fp);
  
  return 0;
}
