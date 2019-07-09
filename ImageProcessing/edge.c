#include "imgfunc.h"
#include <math.h>

void Sobel(Image *img,Image *img_edge,int j,int i);  //ソーベルフィルタ関数

int main(void){
	Image img,img_edge;
	int i,j;
	
	initImage(&img);
	initImage(&img_edge);
	
	if(loadImage("fruits.pgm",&img)==1) return 1;
	
	img_edge=newImage(img.height,img.width,GRAY);
	
	for(j=0;j<img.height;j++){
		for(i=0;i<img.width;i++){
			Sobel(&img,&img_edge,j,i);
		}
	}
	
	if(saveImage("result_6.pgm",&img_edge)==1) return 1;
	
	freeImage(&img);
	freeImage(&img_edge);
	
	printf("finished!");
	return 0;
}

void Sobel(Image *img,Image *img_edge,int j,int i){
	int th=50;  //しきい値
	int s,t;
	int sum=0;  //輪郭の強さ
	int sum_X=0,sum_Y=0;  //水平方向，垂直方向の和
	int ope_X[9]={-1,0,1,-2,0,2,-1,0,1};  //水平方向
	int ope_Y[9]={-1,-2,-1,0,0,0,1,2,1};  //垂直方向
	int WH_ope=3;
	
	for(s=-1;s<2;s++){
		for(t=-1;t<2;t++){
			sum_X+=ope_X[(s+1)*WH_ope+(t+1)]*getPixelGray(j+s,i+t,img);
			sum_Y+=ope_Y[(s+1)*WH_ope+(t+1)]*getPixelGray(j+s,i+t,img);
		}
	}
	sum=sqrt((sum_X*sum_X)+(sum_Y*sum_Y));
	if(sum>=th) sum=0;
	else if(sum<th) sum=255;
	
	setPixelGray(j,i,(unsigned char)sum,img_edge);
}