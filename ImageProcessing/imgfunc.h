#ifndef IMGFUNC_H
#define IMGFUNC_H
#include <stdio.h>
#include <stdlib.h>

/** 画像種類の識別子 */
enum { GRAY=1, RGB=2};


/** 色成分を保持するための構造体　*/
typedef struct{
 unsigned char r;
 unsigned char g;
 unsigned char b;
} Color;


/** 画像を保持するための構造体　*/
typedef struct{
 int imgtype; /*画像種類の識別子。GrayまたはRGB*/
 unsigned int width; /* 画像の幅 */
 unsigned int height; /* 画像の高さ */
 unsigned char *data; /*画素値(unsigned char型またはColor型)の一次配列へのポインタ*/
} Image;


/**
 * 画像を初期化するための関数
 * 
 * 画像構造体の各フィールドを0またはNULLに設定
 * 
 * @param img 画像構造体へのポインタ  
 */
void initImage(Image *img);


/**
 * 画像のメモリを開放するための関数
 * 
 * @param img 画像構造体へのポインタ  
 */
void freeImage(Image *img);

/**
 * 画像を新規作成するための関数
 * 
 * 与えられた大きさと種類に応じて必要なメモリ量を確保した後、これらの
 * 情報を設定した構造体を返す関数。
 * 
 * @param height
 * @param width
 * @param type
 * @return 成功時新規画像へのポインタ。失敗時NULL。
 */
Image newImage( unsigned int height, unsigned int width, int type);


/**
 * 画像ファイルから読み込むための関数
 * 
 * 与えられた名前のファイルはPGMなのかPPMなのかを判別し、ファイルの種類
 * に応じてグレースケール画像またはカラー画像をファイルから読み込み、画像の
 * 構造体に設定する。
 * 
 * @param filename ファイル名の文字列へのポインタ
 * @param img ファイル名の文字列へのポインタ
 * @return 成功時0 失敗時1 
 */
int loadImage(char *filename, Image *img);


/**
 * 画像を保存するための関数
 * 
 * 与えられた画像を種類の識別子に応じてPGMまたはPPMとして保存する関数
 *  * 
 * @param filename ファイル名の文字列へのポインタ
 * @param img ファイル名の文字列へのポインタ
 * @return 成功時0 失敗時1 
 */
int saveImage(char *filename, Image *img);


/**
 * グラースケール画像の指定位置の画素値を取得するための関数
 *  
 * @param j 縦方向の位置
 * @param i 横方向の位置
 * @param img 画像へのポインタ
 * @return 画素値 
 */
unsigned char getPixelGray(int j, int i,Image *img);

/**
 * グラースケール画像の指定位置の画素値を設定するための関数
 *  
 * @param j 縦方向の位置
 * @param i 横方向の位置
 * @param pix 画素値
 * @param img 画像へのポインタ
 */
void setPixelGray(int j,int i, unsigned char pix, Image *img);


/**
 * カラー画像の指定位置の画素の色を取得するための関数
 *  
 * @param j 縦方向の位置
 * @param i 横方向の位置
 * @param img 画像へのポインタ
 * @return 色の構造体 
 */
Color getPixelRGB(int j,int i, Image *img);

/**
 * カラー画像の指定位置の画素の色を設定するための関数
 *  
 * @param j 縦方向の位置
 * @param i 横方向の位置
 * @param clr 画素の色
 * @param img 画像へのポインタ
 */
void setPixelRGB(int j,int i, Color pix, Image *img);

#endif