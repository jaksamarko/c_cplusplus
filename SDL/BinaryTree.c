#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PI 3.14
#define TREE_H 50

SDL_Renderer *renderer;

typedef struct leaf {
    int v;
    struct leaf *l,*r;
}leaf;

leaf * newLeaf(int val){
	leaf * n = malloc(sizeof(leaf));
	n->v = val;
	n->l = n->r = NULL;
	return n;
}

void insertLeaf(leaf **root, int val) {
    if(*root==NULL) {*root=newLeaf(val);}
    else if(val<=(*root)->v) {insertLeaf(&(*root)->l,val);}
    else {insertLeaf(&(*root)->r,val);}
}
const int leafR=12;
void drawLeaves(int x, int y, leaf* root) {
    char buff[4]={'\0'};
    double w=(600-y*2.5)*.2,sp=leafR*.75;

    if(root->l!=NULL) {
        lineRGBA(renderer,x-sp,y+sp,x-w+sp,y+TREE_H-sp,0,0,0,255);
        drawLeaves(x-w,y+TREE_H,root->l);
    }
    if(root->r!=NULL) {
        lineRGBA(renderer,x+sp,y+sp,x+w-sp,y+TREE_H-sp,0,0,0,255);
        drawLeaves(x+w,y+TREE_H,root->r);

    }
    sprintf(buff,"%d",root->v);
    aacircleRGBA(renderer,x,y,leafR,0,0,0,255);
    stringRGBA(renderer,x-7,y-5,buff,0,0,0,255);
}

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


int main(int argc, char *argv[]) {
    srand(time(NULL));
    SDL_Window *window;
    sdl_init("SDL peldaprogram", 800, 600, &window, &renderer);

    leaf *root=NULL;
    int i;
    for(i=0;i<20;i++) {
        insertLeaf(&root,rand()%90+10);
    }

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    drawLeaves(400,20,root);
    SDL_RenderPresent(renderer);

    /* varunk a kilepesre */
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
    }

    /* ablak bezarasa */
    SDL_Quit();

    return 0;
}
