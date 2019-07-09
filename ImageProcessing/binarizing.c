#include "imgfunc.h"

int main(void){
	int i,j;
	unsigned char pix;
	int th=180;  //‚µ‚«‚¢’l
	Image img,img_bin;
	
	initImage(&img);
	initImage(&img_bin);
	
	if(loadImage("fruits.pgm",&img)==1) return 1;
	
	img_bin=newImage(img.height,img.width,GRAY);
	
	for(j=0;j<img.height;j++){
		for(i=0;i<img.width;i++){
			pix=getPixelGray(j,i,&img);
			
			if(pix<=th) pix=0;
			else if(pix>th) pix=255;
			
			setPixelGray(j,i,pix,&img_bin);
		}
	}
	
	if(saveImage("result_4.pgm",&img_bin)==1) return 1;
	
	freeImage(&img);
	freeImage(&img_bin);
	
	printf("finished!");
	return 0;
}