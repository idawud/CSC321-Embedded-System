/*
 * This program divides 2 numbers passed as command line arguments
 * U. Raich, 4. Sept. 2017
 */
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
  double numerator, divisor, result;
  if (argc != 3) {
    printf("Usage: %s numerator divisor\n",argv[0]);
    exit(-1);
  }
  numerator = atof(argv[1]);
  divisor = atof(argv[2]);
  if (abs(divisor) < 1e-10) {
    printf("The divisor is too close to zero, not calculating\n");
    exit (-1);
  }
  else
    printf("%10.4lf / %10.4lf = %10.4lf\n",
	   numerator, divisor, numerator/divisor);
  return 0;
      
    
}
