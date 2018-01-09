#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  double num1, num2, result;
  int i;
  char *operator;
  enum boolean {false,true};
  enum calc {plus,minus,mult,div};
  enum boolean found=false;
  
  typedef struct {
    enum calc toDo;
    char *argVal;
  } ops;
  /*
    define and fill the table with enum/string pairs
  */
  ops table[4] = {{plus,"+"},{minus,"-"},{mult,"*"},{div,"/"}};
  /*
    check if we have the 3 parameters (+ argvc[0] makes them 4!)
  */
  if (argc != 4) {
    printf("usage: %s num1 operator num2\n",argv[0]);
    return -1;
  }
  num1 = atof(argv[1]);
  num2 = atof(argv[3]);
  operator = argv[2];

  printf("%10.4f %s %10.4f\n",num1, operator, num2);

  for (i=plus; i<div+1; i++) {
    if (!strcmp(table[i].argVal,argv[2])) {
      printf("found %s %d\n",argv[2],table[i].toDo);
      found=true;
      break;
    }
  }
  switch (i) {
  case plus:
    printf("plus\n");
    break;
  case minus:
    printf("minus\n");
    break;
  case mult:
    printf("mult\n");
    break;
  case div:
    printf("div\n");
    break;    
  default:
    printf("Unknown operator\n");
  }
  return 0;
}
