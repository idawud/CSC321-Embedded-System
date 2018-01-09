#include <stdio.h>
#define NO_OF_LOOPS 20

void main() {
  int fibonacci[NO_OF_LOOPS];
  int i;
  fibonacci[0]=0;
  fibonacci[1]=1;
  for (i=0;i<NO_OF_LOOPS;i++)
    fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
  for (i=0;i<NO_OF_LOOPS;i++)
    printf("%d ",fibonacci[i]);
  printf("\n");
}
