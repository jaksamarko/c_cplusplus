#define GAME_SPD 60./globalfps

#include "Misc/vehicle_h.h"
#include "Misc/weapon_h.h"
#include "Misc/instances_h.h"
#include "Misc/inventory_h.h"
#include "Misc/world_h.h"
#include "Misc/editor_h.h"
#include "Misc/player_h.h"
#include "Misc/textbox_h.h"
#include "Misc/mobs_h.h"
#include "Misc/gamemode_h.h"
#include "Misc/npc_h.h"
#include "Misc/cutscene_h.h"

#include "Misc/weapon.h"
#include "Misc/instances.h"
#include "Misc/vehicle.h"
#include "Misc/world.h"
#include "Misc/player.h"
#include "Misc/mobs.h"
#include "Misc/gamemode.h"

void view_setup(int w, int h) {
	float dp_w=al_get_display_width(display),dp_h=al_get_display_height(display);
	for(int i=0;i<4;i++) {al_destroy_bitmap(view[i].b);view[i].xport=view[i].yport=view[i].wport=view[i].hport=0;}
	switch(players.cnt) {
		case 1:
			view[0].wport=al_get_display_width(display);
    		view[0].hport=al_get_display_height(display);
		break;
		case 2:
			view[0].wport=view[1].wport=dp_w*0.5; view[1].xport=view[0].wport; view[0].hport=view[1].hport=dp_h;
		break;
		case 3:
		    view[0].wport=view[1].wport=view[1].xport=dp_w*0.5; view[2].wport=dp_w;
			view[0].hport=view[1].hport=view[2].yport=view[2].hport=dp_h*0.5;
		break;
		case 4:
		    for(int i=0;i<4;i++) {
                view[i].wport=dp_w*0.5;view[i].hport=dp_h*0.5;
                view[i].xport=i%2*dp_w*0.5;
                view[i].yport=i/2*dp_h*0.5;
		    }
		break;
	}
	for(int i=0;i<players.cnt;i++) {
        view[i].w=view[i].wport/al_get_display_width(display)*w; view[i].h=view[i].hport/al_get_display_height(display)*h;
        view[i].b=al_create_sub_bitmap(al_get_backbuffer(display),view[i].xport,view[i].yport,view[i].wport,view[i].hport);
    }
}

class _game {
    bool _open;
    public:
    _game() {_open=true;}
    bool opened() {return _open;}
	void close() {_open=false;}
	void open() {_open=true;}
    void start() {
        menu.open();
        players.cnt=menu.get(MENU_PLAY,1)+1;
        view_setup(GAME_W,GAME_H);
        gm.setgm(menu.get(MENU_PLAY,0));
        mobs.start();
        vehicles.start();

        bloods.start();
        powerups.start();
        bullets.start();

        cutscenes.start();

        gm.start();

        vehicles.add(players.p[0].x+500,players.p[0].y,V_TYPE_CAR,0);
        items.spawn(60,0,0,1);
    }
    void step() {
        if(jKbP(ALLEGRO_KEY_ESCAPE)) {close();}
        players.step();
        bullets.step();
        vehicles.step();
        mobs.step();
        bloods.step();
        gm.step();
        tBox.step();
        cutscenes.step();
    }
    void draw() {
        for(int i=0;i<players.cnt;i++) {
            al_set_target_bitmap(view[i].b);
            for(int j=0;j<3;j++) {
                for(int k=0;k<2;k++) {
                    al_draw_bitmap(tex_grass,j*512+(floor(view[i].x/512)*512-view[i].x),k*512+(floor(view[i].y/512)*512-view[i].y),0);
                }
            }
            world.draw(i);
            bloods.draw(i);
            mobs.draw(i);
            vehicles.draw(i);
            npcs.draw(i);
            items.draw(i);
            bullets.draw(i);
            players.draw(i);
        }
        al_set_target_backbuffer(display);
        if(players.cnt>1) {
            for(int i=0;i<players.cnt;i++) {al_draw_rectangle(view[i].xport,view[i].yport,view[i].xport+view[i].wport,view[i].hport+view[i].hport,al_map_rgb(0,0,0),1);}
        }
        if(cutscenes.sz==0) {
            players.draw_gui();
        } else {
            cutscenes.draw();
        }

        tBox.draw();
        al_draw_textf(font,al_map_rgb(0,0,0),0,al_get_font_line_height(font),0,"FPS:%d",realfps);
        gm.draw();
        al_flip_display();
    }
}game;
