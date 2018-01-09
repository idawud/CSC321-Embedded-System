#include <stdio.h>

int main(int argc, char **argv) {
  enum colorName {red,blue,green};
  
  struct {
    enum colorName name;
    unsigned char colorValue[3];
  } colorTable;
  
  colorTable.name = red;
  colorTable.colorValue[0]=255;
  colorTable.colorValue[1]=0;
  colorTable.colorValue[2]=0;

  printf("color name: %d color values: %3d %3d %3d\n",
	 colorTable.name,
	 colorTable.colorValue[0],
	 colorTable.colorValue[1],
	 colorTable.colorValue[2]);
  
}
