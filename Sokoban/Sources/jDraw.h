#ifndef JDRAW_H
#define JDRAW_H

#include"jInit.h"

/*
#define BG_BLACK 0          //A
#define BG_BLUE 16          //B
#define BG_GREEN 32         //C
#define BG_CYAN 48          //D
#define BG_RED 64           //E
#define BG_MAGENTA 80       //F
#define BG_BROWN 96         //G
#define BG_LIGHTGRAY 112    //H
#define BG_DARKGRAY 128     //I
#define BG_LIGHTBLUE 144    //J
#define BG_LIGHTGREEN 160   //K
#define BG_LIGHTCYAN 176    //L
#define BG_LIGHTRED 192     //M
#define BG_LIGHTMAGENTA 208 //N
#define BG_YELLOW 224       //O
#define BG_WHITE 240        //P
*/

#define BG_BLACK 0
#define BG_WHITE 240
#define WHITE 15
#define BG_RED 64

#define SCREEN_W 80
#define SCREEN_H 27
#define SCREEN_SIZE (SCREEN_W*SCREEN_H)

CHAR_INFO chiBuffer[SCREEN_SIZE];

void drawChar(int x, int y, unsigned color, char t);
void drawPixel(int x,int y, unsigned char color);
void drawPixelBlock(int x, int y, int w, int h, unsigned char color);

void clearBuffer(unsigned char color);
void displayBuffer(HANDLE console);

void drawText(int x, int y, unsigned color, char *text);
void drawHelp(movingObjects player, unsigned char *cols);

void drawStaticObjects(staticObjects *f, unsigned char col);
void drawMap(int scale);

void showScreen(HANDLE console,char *screenName);
#endif // JDRAW_H
