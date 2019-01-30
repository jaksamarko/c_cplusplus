#define DEBUG
#define ALLEGRO_5
#include<stdio.h>
#include "J/j.h"

int main() {
    char fname[100];
    bool program=true;
    float anim=0,anim_spd=1;
    int anim_n=0;
    printf("Filename:");
    scanf("%s %d",fname,&anim_n);
    getchar();
    jInit(60,640,480,ALLEGRO_WINDOWED|ALLEGRO_OPENGL_3_0,640,480,"Animation Test (By: Jmarko)");
    jSetAA(true);
    ALLEGRO_FONT *font=al_load_ttf_font("font.ttf",16,0);
    ALLEGRO_BITMAP **spr=jLoadAnim(fname,anim_n);
    if(spr[0]==NULL) {return 1;}
    while(program) {
        switch(jEv()) {
            case ALLEGRO_EVENT_TIMER:
                program=!jKbP(ALLEGRO_KEY_ESCAPE);
                anim+=anim_spd/float(globalfps);
                anim_spd+=(jMsDown()-jMsUp());
            break;
        }
        if(jCanDraw()) {
            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(spr[int(anim)%anim_n],320-al_get_bitmap_width(spr[0])*0.5,240-al_get_bitmap_height(spr[0])*0.5,0);
            al_draw_textf(font,al_map_rgb(0,0,0),0,480-al_get_font_line_height(font),0,"%d FPS|SPD:%.2f",realfps,anim_spd);
            al_flip_display();
        }
    }
    return 0;
}
