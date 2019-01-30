#ifndef JCONSOLE_H
#define JCONSOLE_H

#pragma GCC diagnostic ignored "-Wwrite-strings"

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>

#define DOS 852
#define WIN 1250

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define BG_BLACK 0
#define BG_BLUE 16
#define BG_GREEN 32
#define BG_CYAN 48
#define BG_RED 64
#define BG_MAGENTA 80
#define BG_BROWN 96
#define BG_LIGHTGRAY 112
#define BG_DARKGRAY 128
#define BG_LIGHTBLUE 144
#define BG_LIGHTGREEN 160
#define BG_LIGHTCYAN 176
#define BG_LIGHTRED 192
#define BG_LIGHTMAGENTA 208
#define BG_YELLOW 224
#define BG_WHITE 240

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
CHAR_INFO chiBuffer[80*25];
bool do_loop=false,anykey=false;
char _keys[256]={0};



void drawChar(int x, int y, unsigned char color, unsigned char letter) {
    int pos=y*80+x;
    chiBuffer[pos].Char.AsciiChar=(char) letter;
    chiBuffer[pos].Attributes=color;
}

void drawPixel(int x,int y, unsigned char color) {
    drawChar(x,y,color,' ');
}

void drawText(int x, int y, unsigned char color, const char *text) {
    for(int i=0;i<(int)strlen(text);i++) {
        drawChar(x+i,y,color,text[i]);
    }
}

void clear_buffer(char letter, unsigned char color) {
    for(int i=0;i<80*25;i++) {
        chiBuffer[i].Attributes = color;
        chiBuffer[i].Char.AsciiChar = letter;
    }
}

void display_buffer() {
    SMALL_RECT srctWriteRect = {0,0,79,24};
    COORD coordBufSize = {.X=80,.Y=25},coordBufCoord = {.X=0,.Y=0};
    WriteConsoleOutput(console,chiBuffer,coordBufSize,coordBufCoord,&srctWriteRect);
}

bool key_check(int key) {return _keys[key]==3;}
bool key_check_pressed(int key) {return _keys[key]==2;}
bool key_check_released(int key) {return _keys[key]==1;}
void key_update() {
    anykey=false;
    for(int i=0;i<256;i++) {
        if(GetAsyncKeyState(i)>>8) {
            if(_keys[i]<2) {
                _keys[i]=2;
                anykey=true;
            } else {
                _keys[i]=3;
            }
        } else {
            if(_keys[i]>1) {
                _keys[i]=1;
            } else {
                _keys[i]=0;
            }
        }
    }
}

void drawTextBox(int x, int y, const char *text, unsigned char color, unsigned char bg_color, int delay) {
    int w=0,h=1,temp=0,text_x=0,text_y=0;
    for(int i=0;i<(int)strlen(text);i++) {
        if(text[i]<30) {
            temp=0;
            h++;
        } else {
            temp++;
            if(w<temp) {w=temp;}
        }
    }
    for(int i=0;i<w+2;i++) {
        drawPixel(x+i,y,color);
        drawPixel(x+i,y+h+1,color);
    }
    for(int i=0;i<h+2;i++) {
        drawPixel(x,y+i,color);
        drawPixel(x+w+1,y+i,color);
    }
    for(int i=0;i<w;i++) {
        for(int j=0;j<h;j++) {
            drawPixel(i+x+1,j+y+1,bg_color);
        }
    }
    for(int i=0;i<strlen(text);i++) {
        if(text[i]<30) {text_y++;text_x=0;} else {drawChar(x+1+text_x++,y+1+text_y,bg_color,text[i]);}
        if(delay>0) {display_buffer(); Sleep(delay);}
    }
}

#define ALIGN_LEFT 0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT 2

void drawTextBoxEx(int y, int w, int h, const char *text, unsigned char color, unsigned char bg_color, int delay, char align) {
    int x=0,pos=0,page=0;
    switch(align) {case 1: x=40-w*0.5-1; break; case 2: x=80-w-2; break;}
    for(int i=0;i<w+2;i++) {
        drawPixel(x+i,y,color);
        drawPixel(x+i,y+h+1,color);
    }
    for(int i=0;i<h+2;i++) {
        drawPixel(x,y+i,color);
        drawPixel(x+w+1,y+i,color);
    }
    display_buffer();
    do {
        for(int i=0;i<w;i++) {
            for(int j=0;j<h;j++) {
                drawPixel(i+x+1,j+y+1,bg_color);
            }
        }
        do {
            while(text[pos]<=32) {++pos;}
            drawChar(x+1+pos%w,y+1+(pos-w*h*page)/w,bg_color,text[pos]);
            pos++;
            if(delay>0) {
                Sleep(delay);
                display_buffer();
            }
        } while(((pos)%(w*h)!=0)&&pos<strlen(text));
        if(delay>0) {do {key_update(); Sleep(50);} while(!anykey);} page++;
    } while(pos<strlen(text));
}

void getConsoleText(int boxx, int boxy, char *text, int textx, int texty, int length, unsigned char color) {
    int x=0,y=0,pos,xypos=0;
    key_update();
    boxx-=6;
    for(int i=0;i<9;i++) {
        for(int j=0;j<11;j++) {
            drawPixel(boxx+i,boxy+j,BG_BLACK);
        }
    }
    do {
        pos=strlen(text);
        key_update();
        if(key_check_released(VK_LEFT)) {x--; if(x<0) {x=4-(y==5)*3;}}
        if(key_check_released(VK_UP)) {y--; if(y<0) {y=5;}}
        if(key_check_released(VK_RIGHT)) {x++; if(x>4-(y==5)*3) {x=0;}}
        if(key_check_released(VK_DOWN)) {y++; if(y>5){y=0;}}
        if(y==5&&x>1) {x=0;}
        if(key_check_released(VK_RETURN)) {
            xypos=y*5+x;
            if(xypos<25&&pos<length-1) {
                text[pos++]='A'+xypos;
                text[pos]='\0';
            } else if(xypos==26) {
                if(pos>0) {text[--pos]='\0';}
            }
        }
        for(int i=0;i<27;i++) {
            if(i==25) {
                drawText(boxx+i%5*2,boxy+i/5*2,(x==i%5&&y==i/5)?BG_RED+WHITE:BG_BLACK+WHITE,"DONE");
            } else if(i==26) {
                drawText(boxx+i%5*6,boxy+i/5*2,(x==i%5&&y==i/5)?BG_RED+WHITE:BG_BLACK+WHITE,"DEL");
            } else {
                drawChar(boxx+i%5*2,boxy+i/5*2,(x==i%5&&y==i/5)?BG_RED+WHITE:BG_BLACK+WHITE,'A'+i);
            }
        }
        for(int i=0;i<length-1;i++) {drawChar(textx+i,texty,color,' ');}
        drawText(textx,texty,color,text);
        display_buffer();
        Sleep(50);
    }while(!(key_check_released(VK_RETURN)&&x==0&&y==5));
}

void loop(void(*event)(void),int fps) {
    clock_t dt;
    do_loop=true;
    int sleep_val;
    while(do_loop) {
        dt=clock();
        key_update();
        event();
        display_buffer();
        sleep_val=1000/fps-int(clock()-dt);
        if(sleep_val>0) {Sleep(sleep_val);}
    }
    memset(_keys,0,sizeof(char)*256);
}

void loop_exit() {do_loop=false;}

bool fexists(char *fname) {
    FILE *f=fopen(fname,"r");
    if(f==NULL) {
        return false;
    } else {
        fclose(f);
    }
    return true;
}

#endif // CONSOLE_H
