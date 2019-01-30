class _editor {
        int pos,rot;
    public:
        bool enabled;
        _editor() {enabled=pos=rot=0;}
        void step(unsigned char id);
        void draw(unsigned char id);
};
void _editor::step(unsigned char id) {
    switch(id) {
        case 0:
            if(jKbP(ALLEGRO_KEY_P)) {enabled=!enabled;}
            if(enabled) {
                    pos+=(jMsUp()-jMsDown());
                    if(pos<0) {pos=0;}
                    if(pos==BUILDINGS_COUNT) {pos=BUILDINGS_COUNT-1;}
                    if(jMsP(MB_L)) {
                        world.add(floor((view[id].x+jMsX(view[id].w))/32)*32,
                                  floor((view[id].y+jMsY(view[id].h))/32)*32,
                                  pos,rot);
                    }
                    if(jMsP(MB_M)) {rot=(rot+90)%360;}
            }
        break;
    }
}

void _editor::draw(unsigned char id) {
    al_draw_rotated_bitmap(tex_buildings[pos],
                           al_get_bitmap_width(tex_buildings[pos])*0.5,
                           al_get_bitmap_height(tex_buildings[pos])*0.5,
                           floor((view[id].x+jMsX(view[id].w))/32)*32-view[id].x,
                           floor((view[id].y+jMsY(view[id].h))/32)*32-view[id].y,DegToRad(rot),0);
    al_draw_scaled_rotated_bitmap(tex_buildings[pos],128,128,32,32,
                          64./al_get_bitmap_width(tex_buildings[pos]),
                          64./al_get_bitmap_height(tex_buildings[pos]),DegToRad(rot),0);
}
