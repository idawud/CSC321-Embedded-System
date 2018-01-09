#include <stdio.h>
void main() {
  int a=0, b=1, c, i ;
  int noOfLoops = 20;
  printf("%d %d ",a,b);
  do {
    c = a+b;
    printf("%d ",c);
    a=b;
    b=c;
  } while ((a+b)<100);
  
  printf("\n");
}
