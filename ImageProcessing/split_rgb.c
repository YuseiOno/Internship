#include "imgfunc.h"

int main(void){
	int i,j;
	Image img,img_r,img_g,img_b;
	Color clr;
	
	initImage(&img);
	initImage(&img_r);
	initImage(&img_g);
	initImage(&img_b);
	
	if(loadImage("fruits.ppm",&img)==1) return 1;
	
	img_r=newImage(img.height,img.width,GRAY);
	img_g=newImage(img.height,img.width,GRAY);
	img_b=newImage(img.height,img.width,GRAY);
	
	for(j=0;j<img.height;j++){
		for(i=0;i<img.width;i++){
			clr=getPixelRGB(j,i,&img);
			
			setPixelGray(j,i,clr.r,&img_r);
			setPixelGray(j,i,clr.g,&img_g);
			setPixelGray(j,i,clr.b,&img_b);
		}
	}
	
	if(saveImage("result_3_r.pgm",&img_r)==1) return 1;
	if(saveImage("result_3_g.pgm",&img_g)==1) return 1;
	if(saveImage("result_3_b.pgm",&img_b)==1) return 1;
	
	freeImage(&img);
	freeImage(&img_r);
	freeImage(&img_g);
	freeImage(&img_b);
	
	printf("finished!");
	return 0;
}