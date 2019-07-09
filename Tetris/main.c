#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int canvas[21][20]={0};
int field[21][20]={0};
int block[4][4]={{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}};
int tetramino[7][4][4]={{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
						{{0,0,2,0},{0,0,2,0},{0,0,2,0},{0,0,2,0}},
						{{0,0,0,0},{0,3,0,0},{0,3,0,0},{0,3,3,0}},
						{{0,0,0,0},{0,0,4,0},{0,0,4,0},{0,4,4,0}},
						{{0,5,0,0},{0,5,5,0},{0,5,0,0},{0,0,0,0}},
						{{0,0,0,0},{0,6,6,0},{0,0,6,6},{0,0,0,0}},
						{{0,0,0,0},{0,0,7,7},{0,7,7,0},{0,0,0,0}}};
int title[5][29]={{0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,1,1},
				  {0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0},
				  {0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0},
				  {0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1},
				  {0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,0}};
int go[5][41]={{0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,0},
			   {0,1,0,0,0,0,1,0,1,0,0,1,1,0,1,1,0,0,1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1,0,1},
			   {0,1,0,1,0,0,1,1,1,0,0,1,0,1,0,1,0,0,1,1,1,0,0,1,0,1,0,0,1,0,1,0,0,1,1,1,0,0,1,1,0},
			   {0,1,0,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1,0,1},
			   {0,0,1,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,0,1,0,1}};
int x,y,oneline,twoline,threeline,fourline;
int gameover=0;
int waittime=20000;
int tokuten;
int q1=0,q2=0;   //答え格納
char Q[10000000];   //答えのまとめ
char A;   //質問格納

void Initialize(void);
void ShowGameField(void);
void ShowGameScore(void);
void MoveBlock(int x2,int y2);
int CreateBlock(void);
int CheckOverlap(int x2,int y2);
void AddCanvas(void);
void ControlBlock(void);
void DropBlock(void);
int TurnBlock(void);
void CheckLines(void);
void Title(void);
int ControlTitle(void);
void ru_ru(void);
int keisan(void);
void play(void);
void go_str(void);
int Control_go(void);
void DrawBlock(int view);

int main(void){
	int time=0,a;
	while(1){
		oneline=0;
		twoline=0;
		threeline=0;
		fourline=0;
		gameover=0;
		Title();
		while(1){
			if(kbhit()){
				if(ControlTitle()==1) break;
				if(ControlTitle()==3) goto end;
			}
		}
		system("cls");
		Initialize();
		while(gameover!=1){
			play();
			while(gameover!=1){
				if(kbhit()){
					ControlBlock();
				}
				if(time<waittime){
					time++;
				}
				else{
					DropBlock();
					time=0;
				}
			}
		}
		go_str();
		printf("SCORE　%dpt",tokuten);
		printf("\n\n\n\n　　　 1:タイトルに戻る　　　2:終了");
		if(Control_go()==1) continue;
		else break;
	}
	end:
	return 0;
}

void Initialize(void){
	int i,j;
	for(i=0;i<21;i++){
		for(j=0;j<21;j++){
			if((j==0)||(j==11)||(i==20)||(j==19)){
				canvas[i][j]=9;
			}
			else if(11<j&&19>j&&i==3){
				canvas[i][j]=9;
			}
			else if(11<j&&19>j&&i==8){
				canvas[i][j]=9;
			}
			else{
				canvas[i][j]=0;
			}
		}
	}
	for(i=0;i<21;i++){
		for(j=0;j<20;j++){
			field[i][j]=canvas[i][j];
		}
	}
	CreateBlock();
	ShowGameField();
}

void ShowGameField(void){\
	int i,j;
	system("cls");
	for(i=0;i<21;i++){
		for(j=0;j<20;j++){
			if(field[i][j]==0) printf("　");
			else if(field[i][j]==9) printf("□");
			else if(field[i][j]==1){
				textcolor(0x0E); 
				cprintf("■");
			}
			else if(field[i][j]==2){
				textcolor(0x0B); 
				cprintf("■");
			}
			else if(field[i][j]==3){
				textcolor(6); 
				cprintf("■");
			}
			else if(field[i][j]==4){
				textcolor(9); 
				cprintf("■");
			}
			else if(field[i][j]==5){
				textcolor(5); 
				cprintf("■");
			}
			else if(field[i][j]==6){
				textcolor(0x0C);
				cprintf("■");
			}
			else{
				textcolor(0x0A); 
				cprintf("■");
			}
		}
		printf("\n");
	}
	ShowGameScore();
}

void MoveBlock(int x2,int y2){
	int i,j;
	DrawBlock(0);
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			field[y+i][x+j]-=block[i][j];
		}
	}
	x=x2;
	y=y2;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			field[y+i][x+j]+=block[i][j];
		}
	}
	//ShowGameField();
	DrawBlock(1);
}

int CreateBlock(void){
	int i,j,xx,yy,t_type;
	x=4;
	xx=x;
	y=0;
	yy=y;
	srand(time(0));
	t_type=rand()%7;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			block[i][j]=0;
			block[i][j]=tetramino[t_type][i][j];
		}
	}
	if(CheckOverlap(xx,yy)!=1){
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				field[i][j+4]=canvas[i][j+4]+block[i][j];
			}
		}
	}
	else{
		gameover=1;
		return 1;
	}
	return 0;
}

int CheckOverlap(int x2,int y2){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[i][j]){
				if(canvas[y2+i][x2+j]!=0){
					return 1;
				}
			}
		}
	}
	return 0;
}

void AddCanvas(void){
	int i,j;
	for(i=0;i<21;i++){
		for(j=0;j<12;j++){
			canvas[i][j]=field[i][j];
		}
	}
	CheckLines();
	for(i=0;i<21;i++){
		for(j=0;j<12;j++){
			field[i][j]=canvas[i][j];
		}
	}
}

void ControlBlock(void){
	char key;
	key=getch();
	switch(key){
		case'a':
			if(!CheckOverlap(x-1,y)) MoveBlock(x-1,y);
			break;
		case's':
			if(!CheckOverlap(x,y+1)) MoveBlock(x,y+1);
			break;
		case'd':
			if(!CheckOverlap(x+1,y)) MoveBlock(x+1,y);
			break;
		case' ':
			TurnBlock();
	}
}

void DropBlock(void){
	int a,i;
	if(!CheckOverlap(x,y+1)){
		MoveBlock(x,y+1);
		//system("cls");
		//ShowGameField();
	}
	else{
		AddCanvas();
		CreateBlock();
		ShowGameField();
		play();
	}
}

int TurnBlock(void){
	int i,j;
	int temp[4][4];
	DrawBlock(0);
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			temp[i][j]=block[i][j];
		}
	}
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			block[i][j]=temp[3-j][i];
		}
	}
	if(CheckOverlap(x,y)){
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				block[i][j]=temp[i][j];
			}
		}
		return 1;
	}
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			field[y+i][x+j]-=temp[i][j];
			field[y+i][x+j]+=block[i][j];
		}
	}
	//ShowGameField();
	DrawBlock(1);
	return 0;
}

void CheckLines(void){
	int i,j,k;
	int lines=0;
	int linefull;
	
	while(1){
		for(i=0;i<20;i++){
			linefull=1;
			for(j=1;j<11;j++){
				linefull*=canvas[i][j];
			}
			if(linefull>=1) break;
		}
		if(linefull==0) break;
		lines++;
		for(j=1;j<11;j++){
			canvas[i][j]=0;
		}
		for(k=i;k>0;k--){
			for(j=1;j<11;j++){
				canvas[k][j]=canvas[k-1][j];
			}
		}
	}
	switch(lines){
	case 1:
		oneline++;
		break;
	case 2:
		twoline++;
		break;
	case 3:
		threeline++;
		break;
	case 4:
		fourline++;
		break;
	default:
		break;
	}
}

void Title(void){
	int i,j;
	system("cls");
	printf("\n\n\n\n\n\n");
	for(i=0;i<5;i++){
		for(j=0;j<29;j++){
			if(title[i][j]==0) printf("　");
			else if(title[i][j]==1) printf("■");
		}
		printf("\n");
	}
	printf("\n\n\n\n　　　 1:ゲームスタート　　　2:ルール説明　　　3:終了");
}
	
int ControlTitle(void){
	char key;
	key=getch();
	switch(key){
	case'1':
		return 1;
	case'2':
		ru_ru();
		break;
	case'3':
		return 3;
	}
	return 0;
}
	
void ru_ru(void){
	system("cls");
	printf("***ルール説明***\n\n\n");
	printf("①計算をする\n　※正解するまで、テトラミノの移動・回転が行えない\n\n");
	printf("②テトラミノの移動・回転を駆使して、ハイスコアを狙おう！\n　～テトラミノの移動方法～\n");
	printf("\t｢a｣で左に移動　｢d｣で右に移動　｢s｣で下に加速　｢Space｣で回転\n\n\n");
	printf("※何かキーを押すとタイトルに戻ります");
	if(getche( )){
		Title();
	}
}

int keisan(void){
	HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD bl_coord;
	int syokika;
	int i=0;
	int time=0; 
	int keisan;
	re:
	q1=0;
	q2=0;
	keisan=rand()%3;
	if(keisan==0){
		q1=rand()%100+1;
    	q2=rand()%100+1;
	}
	if(keisan==1){
		while(1){
    		q1=rand()%100+1;
    		q2=rand()%100+1;
			if(q1-q2>0) break;   //答えが正か判断
		}
	}
	if(keisan==2){
		q1=rand()%100+1;
    	q2=rand()%10+1;
	}
	while(gameover!=1){
		bl_coord.X=24;
		bl_coord.Y=4;
		SetConsoleCursorPosition(hStdout,bl_coord);
		if(keisan==0){
			printf("%d+%d　\r",q1,q2);
			sprintf(Q,"%d",syokika);   //以前の計算を0にする
			sprintf(Q,"%d",q1+q2);   //int型をchar型に代入
		}
		if(keisan==1){
    		printf("%d-%d　\r",q1,q2);
			sprintf(Q,"%d",syokika);
    		sprintf(Q,"%d",q1-q2);   //int型をchar型に代入
		}
		if(keisan==2){
			printf("%d*%d　\r",q1,q2);
			sprintf(Q,"%d",syokika);
			sprintf(Q,"%d",q1*q2);   //int型をchar型に代入
		}
		if(kbhit()){
			if(time>=waittime){ 
				DropBlock();
				time=0;
			}
			else{
				A=getch();
				if(A==Q[i]){
					i++;
					if(Q[i]=='\0'){
						break;
					}
				}
				else{
					printf("\a");
					bl_coord.X=24;
					bl_coord.Y=6;
					SetConsoleCursorPosition(hStdout,bl_coord);
					printf("このハゲー！！");
					bl_coord.X=24;
					bl_coord.Y=7;
					SetConsoleCursorPosition(hStdout,bl_coord);
					printf("違うだろー！！");
					goto re;
				}
			}
		}
		if(time<waittime){
			time++;
		}
		else if(time>=waittime){ 
			DropBlock();
			time=0;
		}
		if(!!CheckOverlap(x,y+1)) goto owari;
	}
	bl_coord.X=24;
	bl_coord.Y=6;
	SetConsoleCursorPosition(hStdout,bl_coord);
	printf("　　　　　　　");
	bl_coord.X=24;
	bl_coord.Y=7;
	SetConsoleCursorPosition(hStdout,bl_coord);
	printf("やりますねぇ！");
	owari:
	return 1;
	
}

void play(void){
	int a;
	while(1){
		a=keisan();
		if(a==1) break;
	}
}

void go_str(void){
	int i,j;
	system("cls");
	printf("\n\n\n\n\n\n");
	for(i=0;i<5;i++){
		for(j=0;j<41;j++){
			if(go[i][j]==0) printf("　");
			else if(go[i][j]==1) printf("■");
		}
		printf("\n");
	}
}

int Control_go(void){
	char key;
	key=getch();
	switch(key){
	case'1':
		return 1;
	case'2':
		return 2;
	}
	return 0;
}

void ShowGameScore(void){
	HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD bl_coord;
	bl_coord.X=24;
	bl_coord.Y=1;
	SetConsoleCursorPosition(hStdout,bl_coord);
	tokuten=oneline*1000+twoline*3500+threeline*7000+fourline*10000;
	printf("SCORE:%dpt",tokuten);
}

void DrawBlock(int view){
	HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD bl_coord;
	int i,j;
	for(i=0;i<4;++i){
		for(j=0;j<4;++j){
			if(block[i][j]!=0){
				bl_coord.X=x*2+j*2;
				bl_coord.Y=y+i;
				SetConsoleCursorPosition(hStdout,bl_coord);
				if(view==1){
					if(block[i][j]==1){
						textcolor(0x0E); 
						cprintf("■");
					}
					else if(block[i][j]==2){
						textcolor(0x0B); 
						cprintf("■");
					}
					else if(block[i][j]==3){
						textcolor(6); 
						cprintf("■");
					}
					else if(block[i][j]==4){
						textcolor(9); 
						cprintf("■");
					}
					else if(block[i][j]==5){
						textcolor(5); 
						cprintf("■");
					}
					else if(block[i][j]==6){
						textcolor(0x0C);
						cprintf("■");
					}
					else{
						textcolor(0x0A); 
						cprintf("■");
					}
				}
				else printf("　");
			}
		}
	}
}