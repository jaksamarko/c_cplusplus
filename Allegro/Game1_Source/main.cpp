#define DEBUG
#define ALLEGRO_5
#define ALLEGRO_5_JOY
#define COLLISION
#include "J/j.h"
#include <vector>
using namespace std;

#define GAME_W 800
#define GAME_H 450

ALLEGRO_BITMAP **tex_player[1],**tex_zombie[6],**tex_misc[2],**tex_vehicles,**tex_buildings,**tex_blood,**tex_powups,*tex_grass,**tex_item,**tex_gui;
ALLEGRO_FONT *font;

#include "Headers/menu.h"
#include "Headers/game.h"
#include "Headers/load.h"

int main() {
    jInit(30,GAME_W,GAME_H,ALLEGRO_WINDOWED|ALLEGRO_OPENGL_3_0,GAME_W,GAME_H,"Test");
    init();
    for(int i=0;i<4;i++) {players.p[i].wp[0].equip(WEAPON_GUN);players.set_contr(i,i);}
    do {
        if(menu.opened()) {menu.start();}
        while(menu.opened()) {
            switch(jEv()) {
                case ALLEGRO_EVENT_TIMER: menu.step(); break;
            }
            if(jCanDraw()) {menu.draw();}
        }
        if(game.opened()) {game.start();}
        while(game.opened()) {
            switch(jEv()) {
                case ALLEGRO_EVENT_TIMER: game.step(); break;
            }
            if(jCanDraw()) {game.draw();}
        }
    } while (game.opened()||menu.opened());
    save();
    return 0;
}
