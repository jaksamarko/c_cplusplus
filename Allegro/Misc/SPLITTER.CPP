#include<stdio.h>
#include<allegro5/allegro5.h>
#include<allegro5/allegro_image.h>

int main() {
    ALLEGRO_BITMAP *loaded,*temp;
    char fnamein[150],fnameout[150];
    int wcnt,hcnt,xoff=0,yoff=-1,w,h,spx,spy;
    printf("Relative file path: ");scanf("%s",fnamein);
    printf("Output name(no_format): "); scanf("%s",fnameout);
    printf("W H Xoff Yoff SpaceX SpaceY: ");scanf("%d %d %d %d %d %d",&w,&h,&xoff,&yoff,&spx,&spy);
    al_init();
    al_init_image_addon();
    al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ANY_WITH_ALPHA);
    loaded=al_load_bitmap(fnamein);
    if(loaded==NULL) {printf("ERROR: file not found!(%s)\n",fnamein);}
    temp=al_create_bitmap(w,h);
    al_set_target_bitmap(temp);
    wcnt=(al_get_bitmap_width(loaded)+(spx>0))/(w+spx);
    hcnt=(al_get_bitmap_height(loaded)+(spy>0))/(h+spy);
    for(int i=0;i<wcnt;i++) {
        for(int j=0;j<hcnt;j++) {
            al_clear_to_color(al_map_rgba(255,255,255,0));
            al_draw_bitmap_region(loaded,i*(w+spx)+xoff,j*(h+spy)+yoff,w,h,0,0,0);
            sprintf(fnamein,"%s_%d_%d.png",fnameout,i,j);
            al_save_bitmap(fnamein,temp);
        }
    }
}
