#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

/*--単語--*/
char   word[15][32]={ "printf","void","main","int","long",
                     "double","while","for","break","if",
                     "#include","char","fflush","time","gets"};
void  main( )
{
    char  c[128];                                  // 入力文字列
    int   t0,t1;                                   // 開始,終了時刻
    int   i,j;

    printf("\n***表示された単語をタイプしてください***");
    printf("\n※単語は10回表示されます。\n※どれかキーを押すと始まります。\n");
    getche( );                                     // １文字入力

    t0=time(NULL);                                 // 現在の時刻
    srand(t0);                                     // 乱数の準備

    for ( i=0; i<10; i++ )                         // 10回繰り返す
      {
        j=rand( )%15;                              // 乱数発生(0～14)

        while ( 1 )
          {
            printf("%s: ",&word[j][0]);            // j番目の単語表示
            fflush(stdout);
            gets(c);                               // 文字列入力
            if ( strcmp(c,&word[j][0])==0 ) break; // 文字列一致
            Beep(500,1000);                        // ブザー
          }
      }

    t1=time(NULL);                                 // 現在の時刻
    printf("\nタイムは %d秒でした\n",t1-t0);
}