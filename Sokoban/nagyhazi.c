#include "Sources/jInit.h"
#include "Sources/jDraw.h"
#include "Sources/jLogic.h"

int main() {
    int i;
    char key;
    bool game=false,menu=true;
    bool won,gamePause;
    //Menu

    int menuCurrent=0;

    //Game

    movingObjects player;

    staticObjects *boxes,*goals;

    HANDLE console;
    console = GetStdHandle(STD_OUTPUT_HANDLE);

    while(game||menu) {
        if(menu) {menuInit();}
        while(menu) {
            clearBuffer(0);
            for(i=0;i<MENU_MAX;i++) {
                drawText(4,10+i*2,(menuCurrent==i)?BG_RED+WHITE:BG_WHITE,menuButtons[i]);
            }
            drawText(0,25,WHITE,"W and S to move and ENTER to select!");
            drawText(0,26,WHITE,"Created by Jaksa Marko");
            displayBuffer(console);
            switch(getch()) {
                case 'w':
                    if(--menuCurrent<0) {
                        menuCurrent=MENU_MAX-1;
                    }
                break;
                case 's':
                    menuCurrent=(menuCurrent+1)%(MENU_MAX);
                break;
                case VK_RETURN:
                    menu=false;
                    if(menuCurrent<3) {
                        saveId=menuCurrent;
                        game=true;
                    } else {
                        clearBuffer(BG_BLACK);
                        displayBuffer(console);
                        //Quit screen
                    }
                break;
                case VK_ESCAPE:
                    menu=false;
                break;
            }
        }
        if(!loadLevel(gameLevel[saveId],&goals,&boxes,&player)) {
            showScreen(console,"Finish");
            menu=true; game=false;
        } else {
            player.step=0;
            won=false;
            gamePause=false;
            while(game) {
                if(gamePause) {
                    clearBuffer(BG_BLACK);
                    drawText(21,18,15,"Escape again to quit or any key to continue");
                    displayBuffer(console);
                    switch(getch()) {
                        case VK_ESCAPE:
                            game=false;
                            menu=true;
                        break;
                        default:
                            gamePause=false;
                    }
                } else {
                    clearBuffer(BG_BLACK);
                    drawMap(gameMapScale);
                    drawStaticObjects(goals,cols[2]);
                    drawStaticObjects(boxes,cols[1]);
                    drawPixelBlock(player.x*gameMapScale,player.y*gameMapScale,gameMapScale,gameMapScale,cols[3]);
                    drawHelp(player,cols);
                    displayBuffer(console);
                    player.prevx=player.x;
                    player.prevy=player.y;
                    key=getch();
                    switch(key) {
                        case 'w':
                        case 38: player.y--;  break;
                        case 's':
                        case 40: player.y++;  break;
                        case 'a':
                        case 37: player.x--;  break;
                        case 'd':
                        case 39: player.x++;  break;
                        case VK_ESCAPE:
                            gamePause=true;
                        break;
                    }
                    if(key=='r') {
                        break;
                    }
                    if(player.prevx!=player.x||player.prevy!=player.y) {
                        if(playerCollide(player,boxes)) {
                            player.x=player.prevx;
                            player.y=player.prevy;
                        } else {
                            player.step++;
                            won=checkWin(boxes,goals);
                            if(won) {
                                gameLevel[saveId]++;
                                FILE *f=fopen("save.txt","w");
                                for(i=0;i<3;i++) {
                                    fprintf(f,"%d\n",gameLevel[i]);
                                }
                                fclose(f);
                                showScreen(console,"Won");
                                game=true;
                                break;
                            }
                        }
                    }
                }
            }
            freeMap(drawW);
            freeStaticObjects(goals);
            freeStaticObjects(boxes);
        }
        clearBuffer(BG_BLACK);
        displayBuffer(console);
    }
    return 0;
}
