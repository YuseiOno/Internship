#include "imgfunc.h"

int main(void){
	int i,j;
	int dif=30;  //–¾ˆÃ‚Ì’ö“x
	unsigned char pix,pix_b,pix_d;
	Image img,img_b,img_d;
	
	initImage(&img);
	initImage(&img_b);
	initImage(&img_d);
	
	if(loadImage("fruits.pgm",&img)==1) return 1;
	
	img_b=newImage(img.height,img.width,GRAY);
	img_d=newImage(img.height,img.width,GRAY);
	
	for(j=0;j<img.height;j++){
		for(i=0;i<img.width;i++){
			pix=getPixelGray(j,i,&img);
			pix_b=pix+dif;
			pix_d=pix-dif;
			
			if(pix_b>=255) pix_b=255;
			if(pix_d<0) pix_d=0;
			
			setPixelGray(j,i,pix_b,&img_b);
			setPixelGray(j,i,pix_d,&img_d);
		}
	}
	
	if(saveImage("result_5_b.pgm",&img_b)==1) return 1;
	if(saveImage("result_5_d.pgm",&img_d)==1) return 1;
	
	freeImage(&img);
	freeImage(&img_b);
	freeImage(&img_d);
	
	printf("finished!");
	return 0;
}