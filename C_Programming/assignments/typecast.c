#include <stdio.h>
void main() {
  int a=5,b=3,plus,minus,mult;
  double div;
  plus  = a+b;
  minus = a-b;
  mult  = a*b;
  div  = (double)a/(double)b;
  printf("Results: plus: %d, minus: %d, mult: %d, div: %8.4f\n",
	 plus,minus,mult,div);
}
