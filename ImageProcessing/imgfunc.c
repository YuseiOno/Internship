#include "imgfunc.h"
#include <string.h>

int light;  //�P�x
int nmemb;  //�v�f�̌�

void initImage(Image *img){  //�f�[�^������
	img->imgtype=0;
	img->width=0;
	img->height=0;
	img->data=NULL;
}

void freeImage(Image *img){
	if(img->data!=NULL){
		free(img->data);
		initImage(img);
	}
}

int loadImage(char *filename,Image *img){
	FILE *fp;
	fp=fopen(filename,"rb");
	fscanf(fp,"P%d\n%d %d\n%d",&img->imgtype,&img->width,&img->height,&light);  //�摜�f�[�^�ǂݍ���
	if(img->imgtype==5){  //GRAY
		nmemb=img->width*img->height;
		img->data=(unsigned char*)malloc(nmemb);  //�̈�m��
		img->imgtype=GRAY;  //1
	}
	else if(img->imgtype==6){  //RGB
		nmemb=img->width*img->height*3;
		img->data=(unsigned char*)malloc(nmemb);  //�̈�m��
		img->imgtype=RGB;  //2
	}
	fread(img->data,sizeof(unsigned char),nmemb,fp);  //�o�C�i���t�@�C���̓ǂݍ���
	if(img->data==NULL){
		printf("load error");
		return 1;
	}
	fclose(fp);
	return 0;
}

Image newImage(unsigned int height,unsigned int width,int type){
	Image img;
	if(type==GRAY){
		img.data=(unsigned char*)malloc(width*height);  //�̈�m��
	}
	else if(type==RGB){
		img.data=(unsigned char*)malloc(width*height*3);  //�̈�m��
	}
	if(img.data==NULL){
		printf("creation error");
		exit(1);
	}
	img.height=height;
	img.width=width;
	img.imgtype=type;
	return img;
}

int saveImage(char *filename,Image *img){
	FILE *fp;
	fp=fopen(filename,"wb");
	fprintf(fp,"P%d\n%d %d\n%d",img->imgtype+4,img->width,img->height,light);
	if(img->imgtype==GRAY) nmemb=img->width*img->height;
	else if(img->imgtype==RGB) nmemb=img->width*img->height*3;
	fwrite(img->data,sizeof(unsigned char),nmemb,fp);  //�o�C�i���t�@�C���̏�������
	if(fp==NULL){
		printf("save error");
		return 1;
	}
	fclose(fp);
	return 0;
}

unsigned char getPixelGray(int j,int i,Image *img){
	//���W���͂ݏo���Ƃ��̏���
	if(j<0) j=0;
	else if(j>=img->height) j=img->height-1;
	if(i<0) i=0;
	else if(i>=img->width) i=img->width-1;

	return img->data[j*img->width+i];
}

Color getPixelRGB(int j,int i,Image *img){
	Color clr;
	
	clr.r=img->data[3*(j*img->width+i)];
	clr.g=img->data[3*(j*img->width+i)+1];
	clr.b=img->data[3*(j*img->width+i)+2];
	return clr;
}

void setPixelGray(int j,int i,unsigned char pix,Image *img){
	img->data[j*img->width+i]=pix;
}

void setPixelRGB(int j,int i,Color pix,Image *img){
	img->data[3*(j*img->width+i)]=pix.r;
	img->data[3*(j*img->width+i)+1]=pix.g;
	img->data[3*(j*img->width+i)+2]=pix.b;
}