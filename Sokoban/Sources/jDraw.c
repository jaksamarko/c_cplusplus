#include"jDraw.h"

void drawChar(int x, int y, unsigned color, char t)
{
    int pos=y*SCREEN_W+x;
    chiBuffer[pos].Char.AsciiChar=t;
    chiBuffer[pos].Attributes=color;
}

void drawPixel(int x,int y, unsigned char color) {
    drawChar(x,y,color,' ');
}

void drawPixelBlock(int x, int y, int w, int h, unsigned char color)
{
    int i,j;
    for(i=0; i<w; i++)
    {
        for(j=0; j<h; j++)
        {
            drawPixel(x+i,y+j,color);
        }
    }
}

void clearBuffer(unsigned char color)
{
    int i;
    for(i=0; i<SCREEN_SIZE; i++)
    {
        chiBuffer[i].Attributes = color;
        chiBuffer[i].Char.AsciiChar = ' ';
    }
}

void displayBuffer(HANDLE console)
{
    SMALL_RECT srctWriteRect = {0,0,SCREEN_W-1,SCREEN_H-1};
    COORD coordBufSize = {.X=SCREEN_W,.Y=SCREEN_H},coordBufCoord = {.X=0,.Y=0};
    WriteConsoleOutput(console,chiBuffer,coordBufSize,coordBufCoord,&srctWriteRect);
}

void drawText(int x, int y, unsigned color, char *text)
{
    int i;
    for(i=0; text[i]!='\0'; i++)
    {
        drawChar(x+i,y,color,text[i]);
    }
}

void showScreen(HANDLE console,char *screenName)
{
    char fname[80];
    sprintf(fname,"Assets/screen%s.txt",screenName);
    FILE *f=fopen(fname,"r");
    loadMap(f);
    fclose(f);
    clearBuffer(0);
    drawMap(gameMapScale);
    displayBuffer(console);
    getch();
}

void drawMap(int scale)
{
    int i,j;
    for(i=0; i<drawW; i++) {
        for(j=0; j<drawH; j++) {
            drawPixelBlock(i*scale,j*scale,scale,scale,gameMap[i][j]);
        }
    }
}

void drawStaticObjects(staticObjects *f, unsigned char col)
{
    while(f!=NULL) {
        drawPixelBlock(f->x*gameMapScale,f->y*gameMapScale,gameMapScale,gameMapScale,col);
        f=f->next;
    }
}

void drawHelp(movingObjects player, unsigned char *cols)
{
    char gText[100];
    int i;
    sprintf(gText,"WASD to move.");
    drawText(51,2,15,gText);
    for(i=0; i<4; i++)
    {
        drawPixel(50,3+i,cols[i]);
        switch(i)
        {
        case 0:
            sprintf(gText,"This is the wall :P");
            break;
        case 1:
            sprintf(gText,"Boxes, you have to push them");
            break;
        case 3:
            sprintf(gText,"This is you");
            break;
        case 2:
            sprintf(gText,"Goal, push them here");
            break;
        }
        drawText(51,3+i,15,gText);
    }
    sprintf(gText,"Steps: %d  Press R to replay",player.step);
    drawText(0,26,32+15,gText);
}
