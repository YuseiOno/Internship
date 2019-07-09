#include<GL/glut.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<windows.h>
#include<math.h>

void Display(void);
void Reshape(int,int);
void Timer(int);

int xr=600,yr=600;  //ウィンドウサイズ

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(xr,yr);
	glutCreateWindow("clock");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutInitDisplayMode(GLUT_RGBA);
	glutTimerFunc(500,Timer,0);
	glClearColor(0,0,0,0);
	glutMainLoop();
	return 0;
}

void Display(void){
	int i=0;  //カウント
	int xc=xr/2,yc=yr/2;  //中心座標
	int s,m,h;
	double as,am,ah;  //角度
	int ls,lm,lh;  //針の長さ
	if(xr<yr) ls=0.3*xr,lm=0.3*xr,lh=0.2*xr;
	else ls=0.3*yr,lm=0.3*yr,lh=0.2*yr;
	int xs,ys,xm,ym,xh,yh;
	int x_bou,y_bou,x_bou2,y_bou2;
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	time_t tt;
	struct tm *ts;
	time(&tt);
	ts=localtime(&tt);
	s=ts->tm_sec;
	m=ts->tm_min;
	h=ts->tm_hour;
	as=(2*M_PI*s)/60;
	xs=xc+ls*sin(as);
	ys=yc-ls*cos(as);
	am=(2*M_PI*(60*m+s))/3600;
	xm=xc+lm*sin(am);
	ym=yc-lm*cos(am);
	ah=(2*M_PI*(3600*h+60*m+s))/43200;
	xh=xc+lh*sin(ah);
	yh=yc-lh*cos(ah);
	
	glBegin(GL_POLYGON);
	glColor3ub(191,191,0);
	while(1){
		glVertex2i(xc+(lm*1.25)*sin(i),yc-(lm*1.25)*cos(i));
		if(i==1000) break;
		i++;
	}
	glEnd();
	
	i=0;  //カウントリセット
	
	glBegin(GL_POLYGON);
	glColor3ub(0,0,100);
	while(1){
		glVertex2i(xc+(lm+10)*sin(i),yc-(lm+10)*cos(i));
		if(i==1000) break;
		i++;
	}
	glEnd();
	
	i=1;  //カウントリセット
	
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3ub(255,255,255);
	while(1){
		x_bou=xc+lm*sin((M_PI/6)*i);
		y_bou=yc-lm*cos((M_PI/6)*i);
		glVertex2i(x_bou,y_bou);
		if(i==12) break;
		i++;
	}
	glEnd();
	
	i=1;  //カウントリセット
	
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(255,255,255);
	while(1){
		x_bou=xc+(lm+10)*sin((M_PI/2)*i);
		y_bou=yc-(lm+10)*cos((M_PI/2)*i);
		x_bou2=xc+(lm-25)*sin((M_PI/2)*i);
		y_bou2=yc-(lm-25)*cos((M_PI/2)*i);
		glVertex2i(x_bou,y_bou);
		glVertex2i(x_bou2,y_bou2);
		if(i==4) break;
		i++;
	}
	glEnd();
	
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(191,191,0);
	glVertex2i(xc,yc);
	glVertex2i(xh,yh);
	glEnd();
	
	glLineWidth(6);
	glBegin(GL_LINES);
	glColor3ub(191,191,0);
	glVertex2i(xc,yc);
	glVertex2i(xm,ym);
	glEnd();
	
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(191,191,0);
	glVertex2i(xc,yc);
	glVertex2i(xs,ys);	
	glEnd();
	
	glFlush();
}

void Reshape(int w,int h){
	xr=w;
	yr=h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0,w,0,h);
	glScaled(1,-1,1);
	glTranslated(0,-h,0);
}

void Timer(int value){
	glutPostRedisplay();
	glutTimerFunc(500,Timer,0);
}

//gcc -Wall -I/usr/include/opengl -o reshapewindow.exe reshapewindow.c -lglpng -lglut32 -lglu32 -lopengl32