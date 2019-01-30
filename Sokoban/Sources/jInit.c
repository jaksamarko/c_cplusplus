 #include"jInit.h"

 void pushObject(staticObjects **first,int x,int y) {
    staticObjects *New=(staticObjects*) malloc(sizeof(staticObjects));
    New->x=x;
    New->y=y;
    New->next=*first;
    *first=New;
}

void err(char *t) {
    printf("%s",t);
    exit(-1);
}

void menuInit()
{
    int i;
    char menuText[20];
    FILE *f=fopen("save.txt","r");
    if(f==NULL)  //Ha nincs save fájl,akkor hozzon létre egyet!
    {
        f=fopen("save.txt","w");
        for(i=0; i<3; i++)
        {
            fprintf(f,"%d\n",0);
        }
        fclose(f);
        f=fopen("save.txt","r");
    }
    for(i=0; i<3; i++) //Beolvassa a játékmentéseket
    {
        fscanf(f,"%d\n",&gameLevel[i]);
        if(gameLevel[i])
        {
            sprintf(menuText,"Continue Level %d",gameLevel[i]);
            strcpy(menuButtons[i],menuText);
        }
        else
        {
            strcpy(menuButtons[i],"New save");
        }
    }
    strcpy(menuButtons[3],"Exit");
    fclose(f);
}

void loadMap(FILE *filePtr)
{
    int c,filePos,i=0,j=0;
    int currW;
    drawW=drawH=currW=0;
    filePos=ftell(filePtr);
    while(1)
    {
        c=fgetc(filePtr);
        if(c=='\n') {
            drawH++;
            currW=0;
        } else if(c==EOF) {
            if(currW) {
                drawH++; //Ha véletlenül nem lenne enter az utolsó sor után
            }
            break;
        } else {
            if(++currW>drawW) {drawW=currW;}
        }
    }
    fseek(filePtr,filePos,SEEK_SET);
    gameMap=(unsigned char**) malloc(sizeof(unsigned char*)*drawW);
    for(i=0;i<drawW;i++) {
        gameMap[i]=(unsigned char*) calloc(sizeof(unsigned char),drawH);
    }
    for(j=0;j<drawH;j++) {
        for(i=0;(c=fgetc(filePtr))>32;i++) {
            gameMap[i][j]=(c-'A')*16;
        }
    }
    if(drawH==0) {
        err("Cant load map");
    } else {
        gameMapScale=25/(float)drawH;
    }
}

bool loadLevel(int currentLevel, staticObjects **goals, staticObjects **boxes, movingObjects* player)
{
    char mapName[25];
    int i;
    int bX,bY,gX,gY;
    sprintf(mapName,"Assets/map%d.txt",currentLevel);
    FILE *f=fopen(mapName,"r");
    if(f==NULL) {
        return false;
    }
    if(fscanf(f,"%c,%c,%c,%c\n%d,%d\n",&cols[0],&cols[1],&cols[2],&cols[3],&player->x,&player->y)!=6) {
        err("Error on load map: not enough parameter!");
    }
    for(i=0; i<4; i++) {
        cols[i]=(cols[i]-'A')*16;
    }

    player->step=0;
    *boxes=*goals=NULL;

    while(fscanf(f,"%d,%d %d,%d\n",&bX,&bY,&gX,&gY)==4) {
        pushObject(boxes,bX,bY);
        pushObject(goals,gX,gY);
    }
    loadMap(f);
    fclose(f);
    return true;
}

void freeStaticObjects(staticObjects *l) {
    staticObjects *c=l;
    while(l!=NULL) {
        c=l;
        l=l->next;
        free(c);
    }
}

void freeMap(int w) {
    for(w-=1;w>=0;w--)
        free(gameMap[w]);
    free(gameMap);
}
