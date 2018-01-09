#include <stdio.h>
int main() {
  FILE *outputFile;
  int a=5,b=3,plus,minus,mult;
  double div;
  /*
    here we open the file
  */
  if ((outputFile = fopen("/tmp/resulFile.txt","w")) < 0) {
      fprintf(stderr,"Could not open output file /tmp/resulFile.txt\n");
      return -1;
    }
  plus  = a+b;
  minus = a-b;
  mult  = a*b;
  div  = (double)a/(double)b;
  fprintf(outputFile,"Results: plus: %d, minus: %d, mult: %d, div: %8.4f\n",
	 plus,minus,mult,div);
  fclose(outputFile);
  return 0;
}
