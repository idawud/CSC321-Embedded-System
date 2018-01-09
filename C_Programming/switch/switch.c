#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  double val1,val2,result;
  char operator;
  
  if (argc != 4) {
    printf("usage: %s val1 operator val2\n",argv[0]);
    exit(-1);
  }

  val1 = atof(argv[1]);
  val2 = atof(argv[3]);
  operator = (argv[2])[0];
  switch (operator) {
  case '+':
    printf("%10.4f added to %10.4f\n",val1,val2);
    break;
  case '-':
    printf("%10.4f minus %10.4f\n",val1,val2);
    break;
  case '*':
    printf("%10.4f multiplied by %10.4f\n",val1,val2);
    break;
  case '/':
    printf("%10.4f divided by %10.4f\n",val1,val2);
    break;
  default:
    printf("Invalid operator!\n");
    exit(-1);
  }
}
