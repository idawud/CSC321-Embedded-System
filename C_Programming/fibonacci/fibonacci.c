#include <stdio.h>
void main() {
  int a=0, b=1, c, i ;
  int noOfLoops = 20;
  printf("%d %d ",a,b);
  for (i=0;i<noOfLoops;i++) {
    c = a+b;
    printf("%d ",c);
    a=b;
    b=c;
  }
  printf("\n");
}
