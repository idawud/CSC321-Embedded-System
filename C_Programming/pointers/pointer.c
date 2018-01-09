#include <stdio.h>
#include <string.h>

int main() {
  int a=5,i;
  char *hello = "Hello World!";
  char *helloPtr = hello;
  int *aptr= &a; /* tell me the place in memory where the value of a is stored */
  printf("a: %d,  aptr: 0x%lx, the content of the place where aptr points to %d\n",
	 a, (long)aptr, *aptr);
  for(i=0;i<strlen(hello)+1;i++)
    printf("0x%02x ",*helloPtr++); 
  printf("%s\n",hello);
  return 0;
}
