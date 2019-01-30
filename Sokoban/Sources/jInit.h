#ifndef JINIT_H
#define JINIT_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define SAVE_MAX 3
#define MENU_MAX SAVE_MAX+1

typedef struct movingObjects
{
    int x,y,prevx,prevy,step;
} movingObjects;
typedef struct staticObjects
{
    int x,y;
    struct staticObjects *next;
} staticObjects;

//Menu variables
char menuButtons[4][30];

//Game variables
int gameLevel[3],saveId;
unsigned char cols[4];
/*
    0: Collision color
    1: Box color
    2: Goal color
    3: Player color
*/


unsigned char **gameMap;         //Array of the map data
int drawW,drawH;
int gameMapScale;

void pushObject(staticObjects **first,int x,int y);

void err(char *t);

void menuInit();

void loadMap(FILE *filePtr);

bool loadLevel(int currentLevel, staticObjects **goals, staticObjects **boxes, movingObjects* player);

void freeStaticObjects(staticObjects *l);
void freeMap(int w);

#endif
