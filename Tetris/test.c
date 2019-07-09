#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

void  main( )
{
  int   n,nO=-1;   // キー番号
  int   Hz;        // Beep音周波数

    system("cls");                        // 画面消去

    printf(" \n");
    printf(" |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf(" |                 キーボードピアノ（Beep音）                  |\n");
    printf(" |          ※Shiftキーを押すと１オクターブ上がります          |\n");
    printf(" |          ※長押しはできません                               |\n");
    printf(" |                                                             |\n");
    printf(" *:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*\n");
    printf("  |                                                           | \n");
    printf("  |----,----,----,----,----,----,----,----,----,----,----,----| \n");
    printf("  |ソ＃|ラ＃|    |ド＃|レ＃|    |ﾌｧ＃|ソ＃|ラ＃|    |ド＃|レ＃| \n");
    printf("  | Ａ | Ｓ | Ｄ | Ｆ | Ｇ | Ｈ | Ｊ | Ｋ | Ｌ | ； | ： | ］ | \n");
    printf("  '----'----'----'----'----'----'----'----'----'----'----'----' \n");
    printf("    | ラ | シ | ド | レ | ミ | ﾌｧ | ソ | ラ | シ | ド | レ |    \n");
    printf("    | Ｚ | Ｘ | Ｃ | Ｖ | Ｂ | Ｎ | Ｍ | ， | ． | ／ | ＼ |    \n");
    printf("    '----'----'----'----'----'----'----'----'----'----'----'    \n");

    while ( 1 )
      {
        if ( kbhit( )==0 )               // キーが押されてない
          { n=-1; continue; }            // キー番号を無効にする

        nO=n;                            // 前のキー番号保存
        n=getch( );                      // １文字読む（キーボードバッファクリア）
        if ( n==27 ) break;              // ESCで終了
        if ( n==nO ) continue;           // 同じキーを押したまま

        switch (n)
          {
            case  97: Hz= 208; break;    // a ソ＃
            case 115: Hz= 233; break;    // s ラ＃
            case 102: Hz= 277; break;    // f ド＃
            case 103: Hz= 311; break;    // g レ＃
            case 106: Hz= 370; break;    // j ファ＃
            case 107: Hz= 415; break;    // k ソ＃
            case 108: Hz= 466; break;    // l ラ＃
            case  58: Hz= 554; break;    // ; ド＃
            case  93: Hz= 622; break;    // ] レ＃

            case 122: Hz= 220; break;    // z ラ
            case 120: Hz= 247; break;    // x シ
            case  99: Hz= 262; break;    // c ド
            case 118: Hz= 294; break;    // v レ
            case  98: Hz= 330; break;    // b ミ
            case 110: Hz= 349; break;    // n ファ
            case 109: Hz= 392; break;    // m ソ
            case  44: Hz= 440; break;    // , ラ
            case  46: Hz= 494; break;    // . シ
            case  47: Hz= 523; break;    // / ド
            case  92: Hz= 587; break;    // \ レ

            //--Shift--
            case  65: Hz= 415; break;    // A ソ＃
            case  83: Hz= 466; break;    // S ラ＃
            case  70: Hz= 554; break;    // F ド＃
            case  71: Hz= 622; break;    // G レ＃
            case  72: Hz= 740; break;    // J ファ＃
            case  74: Hz= 831; break;    // K ソ＃
            case  76: Hz= 932; break;    // L ラ＃
            case  43: Hz=1109; break;    // + ド＃
            case 125: Hz=1245; break;    // ] レ＃

            case  90: Hz= 440; break;    // Z ラ
            case  88: Hz= 494; break;    // X シ
            case  67: Hz= 523; break;    // C ド
            case  86: Hz= 587; break;    // V レ
            case  66: Hz= 659; break;    // B ミ
            case  78: Hz= 698; break;    // N ファ
            case  77: Hz= 784; break;    // M ソ
            case  60: Hz= 880; break;    // < ラ
            case  62: Hz= 988; break;    // > シ
            case  63: Hz=1047; break;    // ? ド
            case  95: Hz=1175; break;    // _ レ

            default : Hz=   0;
          }

        Beep(Hz,200);                    // 200ミリ秒鳴らす
      }
}
   