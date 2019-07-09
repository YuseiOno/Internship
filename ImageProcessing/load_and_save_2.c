#include "imgfunc.h"

int main(void){
	int i,j;
	Image img;
	
	initImage(&img);
	
	if(loadImage("fruits.ppm",&img)==1) return 1;
	if(saveImage("result_2.ppm",&img)==1) return 1;
	
	freeImage(&img);
	
	printf("finished!");
	return 0;
}