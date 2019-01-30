#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct pt {
    int x,y;
}pt;

/* kulon fuggvenybe, hogy olvashatobb legyen */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

int pointDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

int ellipseDistance(pt* Pts, int x, int y) {
    return (pointDistance(x,y,Pts[0].x,Pts[0].y)+pointDistance(x,y,Pts[1].x,Pts[1].y));
}

void drawEllipse(SDL_Renderer *r, pt* Pts, int rad, int eps) {
    int i,j;
    int dist=(int)fabs(Pts[0].x-Pts[1].x);
    for(i=0;i<800;i++) {
        for(j=0;j<600;j++) {
            if(fabs(ellipseDistance(Pts,i,j)-(rad+dist))<eps) {
                pixelRGBA(r,i,j,255,0,0,255);
            }
        }
    }
}


int main(int argc, char *argv[]) {
    /* ablak létrehozása */
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("SDL peldaprogram", 800, 600, &window, &renderer);

    int i;
    SDL_Event ev;

    int state=-1;

    char strOutput[50];
    pt Points[2];
    for(i=0;i<2;i++) {
        Points[i].y=300;
        Points[i].x=400+i*100;
    }
    int r=30;
    int eps=2;

    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch(ev.type) {
            case SDL_MOUSEBUTTONDOWN:
                if(fabs(ellipseDistance(Points,ev.button.x,ev.button.y)-(r+pointDistance(Points[0].x,0,Points[1].x,0)))<3) { //A könnyeb kijelölés érdekében
                    state=2;
                } else {
                    for(i=0;i<2;i++) {
                        if(pointDistance(ev.button.x,ev.button.y,Points[i].x,Points[i].y)<=4) {
                            state=i;
                            break;
                        }
                    }
                }
            break;
            case SDL_MOUSEBUTTONUP:
                state=-1;
            break;
        }

        if(state!=-2) {
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            drawEllipse(renderer,Points,r,eps);
            for(i=0;i<2;i++) {
                filledCircleRGBA(renderer,Points[i].x,Points[i].y,4,(state==i)*255,(state!=i)*255,0,255);
            }

            sprintf(strOutput,"F1: x=%d y=%d F2: x=%d y=%d Distance: %d %d",Points[0].x,Points[0].y,Points[1].x,Points[1].y,r,state);
            stringRGBA(renderer, 0, 580, strOutput, 255, 255, 255, 255);

            SDL_RenderPresent(renderer);
        }

        switch(state) {
            case 2:
                r=ellipseDistance(Points,ev.button.x,ev.button.y)-pointDistance(Points[0].x,0,Points[1].x,0);
            break;
            case 0:
            case 1:
                Points[state].x=ev.button.x;
                Points[state].y=ev.button.y;
            break;
            case -1:
                state=-2;
            break;
            //-2: nem rajzol ujra állapot
        }

    }
    SDL_Quit();

    return 0;
}
