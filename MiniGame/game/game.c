#include<GL/glut.h>
#include<GL/glpng.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

void Display(void);
void Reshape(int,int);
void PutSprite(int,int,int,pngInfo *);
void Mouse(int,int,int,int);
void Keyboard(unsigned char,int,int);
void Timer(int);
void Enemy(void);
int Hantei(void);
int EneHantei(int);
int TamaHantei(void);
int EneTamaHantei(int);
void Map(void);
void Tama(void);

//PNG画像を読み込むための変数
GLuint img[4];
pngInfo info[4];
GLuint mapparts[3];
pngInfo mapinf[3];
GLuint me[8];
pngInfo meinf[8];
GLuint ene[8];
pngInfo eneinf[8];

//グローバル変数
//プレイヤー関連
int px=500,py=800;  //戦車の位置
int pt=0;  //戦車の向き
int ptx=-100,pty=-100;  //玉の位置
int pto=0;  //発射時の戦車の向き
int A=0;  //玉を出す判断
//敵関連
int tx[5],ty[5];  //敵の戦車の位置
int tt[5];  //敵の戦車の向き
int ttx[5],tty[5];  //敵の玉の位置
int tto[5];  //発射時の敵の戦車の向き
//その他
int gameover=1;  //ゲームオーバーか判断
int map[1000][1000];  //マップ
int T=0;  //敵消滅カウンタ
int syoumetu[5]={0,0,0,0,0};


int main(int argc,char **argv)
{
	char fname[20],f[20];
	int i;
	
	glutInit(&argc,argv);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("tank game");
	glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA);
	glClearColor(0.0,0.0,1.0,1.0);
	
	//テクスチャのアルファチャネルを有効にする設定
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	
	//PNG画像の読み込み
	for(i=0;i<4;i++)
	{
		sprintf(fname,"img%02d.png",i+1);
		img[i]=pngBind(fname,PNG_NOMIPMAP,PNG_ALPHA,&info[i],GL_CLAMP,GL_NEAREST,GL_NEAREST);
	}
	for(i=0;i<3;i++)
	{
		sprintf(fname,"mapparts%02d.png",i+1);
		mapparts[i]=pngBind(fname,PNG_NOMIPMAP,PNG_ALPHA,&mapinf[i],GL_CLAMP,GL_NEAREST,GL_NEAREST);
	}
	for(i=0;i<8;i++)
	{
		sprintf(f,"me%02d.png",i+1);
		me[i]=pngBind(f,PNG_NOMIPMAP,PNG_ALPHA,&meinf[i],GL_CLAMP,GL_NEAREST,GL_NEAREST);
	}
	for(i=0;i<8;i++)
	{
		sprintf(f,"ene%02d.png",i+1);
		ene[i]=pngBind(f,PNG_NOMIPMAP,PNG_ALPHA,&eneinf[i],GL_CLAMP,GL_NEAREST,GL_NEAREST);
	}
	
	//コールバック関数の登録
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutTimerFunc(50,Timer,0);
	
	
	//イベントループ突入
	glutMainLoop();
	
	return 0;
}


void Reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0,w,0,h);
	glScaled(1,-1,1);
	glTranslated(0,-h,0);
}


void Display(void)
{
	int i;
	
	Map();
	
	if(gameover==1)  //タイトル
	{
		PutSprite(img[0],0,0,&info[0]);
		glFlush();
		Enemy();
		for(i=0;i<5;i++)
		{
			ttx[i]=tx[i];
			tty[i]=ty[i];
			tto[i]=tt[i];
		}
	}
	if(gameover==2)  //ルール説明
	{
		PutSprite(img[1],0,0,&info[1]);
		glFlush();
	}
	if(gameover==3)  //ゲームオーバー
	{
		PutSprite(img[2],0,0,&info[2]);
		glFlush();
	}
	
	if(gameover==4)  //ゲームクリア
	{
		PutSprite(img[3],0,0,&info[3]);
		glFlush();
	}
	
	else if(gameover==0)
	{
		srand(time(NULL));
		PutSprite(mapparts[0],0,0,&mapinf[0]);
		glFlush();
		PutSprite(mapparts[1],600,100,&mapinf[1]);
		glFlush();
		PutSprite(mapparts[1],100,700,&mapinf[1]);
		glFlush();
		
		for(i=0;i<5;i++)
		{
			switch(rand()%4+1)
			{
				case 1:
				switch(rand()%4)
				{
					case 0: 
						tt[i]=0;
						break;
					case 1: 
						tt[i]=1;
						break;
					case 2: 
						tt[i]=2;
						break;
					case 3:
						tt[i]=3;
						break;
					default:
						printf("エラー");
						exit(0);
				}
				default:
					if(tt[i]==0&&EneHantei(i)==1) ty[i]-=2;
					if(tt[i]==2&&EneHantei(i)==1) ty[i]+=2;
					if(tt[i]==3&&EneHantei(i)==1) tx[i]-=2;
					if(tt[i]==1&&EneHantei(i)==1) tx[i]+=2;
			}
			
			if(EneTamaHantei(i)!=1)
			{
				ttx[i]=tx[i];
				tty[i]=ty[i];
				tto[i]=tt[i];
			}
			
			if(tto[i]==0&&EneTamaHantei(i)==1) tty[i]-=20;
			else if(tto[i]==2&&EneTamaHantei(i)==1) tty[i]+=20;
			else if(tto[i]==3&&EneTamaHantei(i)==1) ttx[i]-=20;
			else if(tto[i]==1&&EneTamaHantei(i)==1) ttx[i]+=20;
			
			if(syoumetu[i]==0){
				PutSprite(ene[4+tto[i]],ttx[i],tty[i],&eneinf[4+tto[i]]);
				glFlush();
				
				PutSprite(ene[tt[i]],tx[i],ty[i],&eneinf[tt[i]]);
				glFlush();
			}
		}
		
		Tama();
		
		PutSprite(me[pt],px,py,&meinf[pt]);
		glFlush();
	}
}


void PutSprite(int num,int x,int y,pngInfo *info)
{
	int w,h;  //テクスチャの幅と高さ
	
	w=info->Width;  //テクスチャの幅と高さを取得する
	h=info->Height;
	
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,num);
	glColor4ub(255,255,255,255);
	
	glBegin(GL_QUADS);  //幅w，高さhの四角形
	
	glTexCoord2i(0,0);
	glVertex2i(x,y);
	
	glTexCoord2i(0,1);
	glVertex2i(x,y+h);
	
	glTexCoord2i(1,1);
	glVertex2i(x+w,y+h);
	
	glTexCoord2i(1,0);
	glVertex2i(x+w,y);
	
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 119:  //w
			pt=0;
			if(Hantei()==1)
			{
				py-=2;
			}
			break;
		case 115:  //s
			pt=2;
			if(Hantei()==1)
			{
				py+=2;
			}
			break;
		case 97:  //a
			pt=3;
			if(Hantei()==1)
			{
				px-=2;
			}
			break;
		case 100:  //d
			pt=1;
			if(Hantei()==1)
			{
				px+=2;
			}
			break;
		case 32:  //スペースキー
			ptx=px;
			pty=py;
			pto=pt;
			A=1;
			break;
		case 27:  //Ecs
			printf("Escキーで終了しました");
			exit(0);
			break;
		case 114:  //r
			gameover=2;
			break;
		case 13:  //Enter
			gameover=0;
			break;
	}
}


void Timer(int a)
{
	glutPostRedisplay();  //再描画させる
	glutTimerFunc(50,Timer,0);
}


void Enemy(void)
{
	int i,x,y,t;
	
	for(i=0;i<5;i++)
	{
		while(1)
		{
			x=rand()%1000+1;
			y=rand()%1000+1;
			t=rand()%4;
			if(map[y][x]==0&&map[y+50][x]==0&&map[y][x+50]==0&&map[y+50][x+50]==0) break;
		}
		tx[i]=x;
		ty[i]=y;
		tt[i]=t;
	}
}


int Hantei(void)
{
	switch(pt)
	{
		case 0:
			if(map[py-2][px]==0&&map[py-2][px+49]==0) return 1;
			else return 0;
			break;
		case 2:
			if(map[py+52][px]==0&&map[py+52][px+49]==0) return 1;
			else return 0;
			break;
		case 3:
			if(map[py][px-2]==0&&map[py+49][px-2]==0) return 1;
			else return 0;
			break;
		case 1:
			if(map[py][px+52]==0&&map[py+49][px+52]==0) return 1;
			else return 0;
			break;
		default:
			return 0;
	}
	return 0;
}


int EneHantei(int i)
{
	switch(tt[i])
	{
		case 0:
			if(map[ty[i]-2][tx[i]]==0&&map[ty[i]-2][tx[i]+49]==0) return 1;
			else return 0;
			break;
		case 2:
			if(map[ty[i]+52][tx[i]]==0&&map[ty[i]+52][tx[i]+49]==0) return 1;
			else return 0;
			break;
		case 3:
			if(map[ty[i]][tx[i]-2]==0&&map[ty[i]+49][tx[i]-2]==0) return 1;
			else return 0;
			break;
		case 1:
			if(map[ty[i]][tx[i]+52]==0&&map[ty[i]+49][tx[i]+52]==0) return 1;
			else return 0;
			break;
		default:
			return 0;
	}
	return 0;
}


int TamaHantei(void)
{
	int i;
	
	switch(pto)
	{
		case 0:
			if(map[pty-20][ptx+21]==0&&map[pty-20][ptx+27]==0)
			{
				return 1;
			}
			else
			{
				for(i=0;i<5;i++)
				{
					if(map[pty-20][ptx+21]==i+2||map[pty-20][ptx+27]==i+2)
					{
						syoumetu[i]=1;
						return 0;
					}
				}
			}
			break;
		case 2:
			if(map[pty+70][ptx+21]==0&&map[pty+70][ptx+27]==0)
			{
				return 1;
			}
			else
			{
				for(i=0;i<5;i++)
				{
					if(map[pty+70][ptx+21]==i+2||map[pty+70][ptx+27]==i+2)
					{
						syoumetu[i]=1;
						return 0;
					}
				}
			}
			break;
		case 3:
			if(map[pty+21][ptx-20]==0&&map[pty+27][ptx-20]==0)
			{
				return 1;
			}
			else
			{
				for(i=0;i<5;i++)
				{
					if(map[pty+21][ptx-20]==i+2||map[pty+27][ptx-20]==i+2)
					{
						syoumetu[i]=1;
						return 0;
					}
				}
			}
			break;
		case 1:
			if(map[pty+21][ptx+70]==0&&map[pty+27][ptx+70]==0)
			{
				return 1;
			}
			else
			{
				for(i=0;i<5;i++)
				{
					if(map[pty+21][ptx+70]==i+2||map[pty+27][ptx+70]==i+2)
					{
						syoumetu[i]=1;
						return 0;
					}
				}
			}
			break;
		default:
			return 0;
	}
	return 0;
}


int EneTamaHantei(int i)
{
	switch(tto[i])
	{
		case 0:
			if(map[tty[i]-20][ttx[i]+21]==0&&map[tty[i]-20][ttx[i]+27]==0)
			{
				return 1;
			}
			else if((map[tty[i]-20][ttx[i]+21]==1||map[tty[i]-20][ttx[i]+27]==1)&&syoumetu[i]==0)
			{
				gameover=3;
				return 0;
			}
			break;
		case 2:
			if(map[tty[i]+70][ttx[i]+21]==0&&map[tty[i]+70][ttx[i]+27]==0)
			{
				return 1;
			}
			else if((map[tty[i]+70][ttx[i]+21]==1||map[tty[i]+70][ttx[i]+27]==1)&&syoumetu[i]==0)
			{
				gameover=3;
				return 0;
			}
			break;
		case 3:
			if(map[tty[i]+21][ttx[i]-20]==0&&map[tty[i]+27][ttx[i]-20]==0)
			{
				return 1;
			}
			else if((map[tty[i]+21][ttx[i]-20]==1||map[tty[i]+27][ttx[i]-20]==1)&&syoumetu[i]==0)
			{
				gameover=3;
				return 0;
			}
			break;
		case 1:
			if(map[tty[i]+21][ttx[i]+70]==0&&map[tty[i]+27][ttx[i]+70]==0)
			{
				return 1;
			}
			else if((map[tty[i]+21][ttx[i]+70]==1||map[tty[i]+27][ttx[i]+70]==1)&&syoumetu[i]==0)
			{
				gameover=3;
				return 0;
			}
			break;
		default:
			return 0;
	}
	return 0;
}


void Map(void)
{
	int i,j,k;
	int check=0;
	
	//マップを初期設定に戻す
	//0->なし 1->プレーヤー 2->敵1 3->敵2 4->敵3 5->敵4 6->敵5 7->壁
	for(i=0;i<1000;i++)
	{
		for(j=0;j<1000;j++)
		{
			map[i][j]=0;
			if(i<=20||i>=980)
			{
				map[i][j]=7;
			}
			else if(i>20&&i<980)
			{
				if(j<=20||j>=980)
				{
					map[i][j]=7;
				}
			}
			if(i>=100&&i<=300&&j>=600&&j<=900)
			{
				map[i][j]=7;
			}
			if(i>=700&&i<=900&&j>=100&&j<=400)
			{
				map[i][j]=7;
			}
		}
	}
	
	//プレーヤーと敵の位置を格納
	//0->なし 1->プレーヤー 2->敵1 3->敵2 4->敵3 5->敵4 6->敵5 7->壁
	for(i=0;i<5;i++)
	{
		for(j=0;j<49;j++)
		{
			for(k=0;k<49;k++)
			{
				map[ty[i]+j][tx[i]+k]=2+i;
				if(syoumetu[i]==1)
				{
					map[ty[i]+j][tx[i]+k]=0;
				}
				map[py+j][px+k]=1;
			}
		}
	}
	for(i=0;i<1000;i++)
	{
		for(j=0;j<1000;j++)
		{
			if(map[i][j]==2||map[i][j]==3||map[i][j]==4||map[i][j]==5||map[i][j]==6) check++;
		}
	}
	if(check==0) gameover=4;  //ゲームクリア
}


void Tama(void)
{
	if(A==1)
	{
		if(pto==0&&TamaHantei()==1) pty-=20;
		else if(pto==2&&TamaHantei()==1) pty+=20;
		else if(pto==3&&TamaHantei()==1) ptx-=20;
		else if(pto==1&&TamaHantei()==1) ptx+=20;
		
		PutSprite(me[4+pto],ptx,pty,&meinf[4+pto]);
		glFlush();
	}
}

//gcc -Wall -I/usr/include/opengl -o game.exe game.c -lglpng -lglut32 -lglu32 -lopengl32