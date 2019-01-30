#define BUILDINGS_COUNT 9
struct buildings {
    int x,y,cx,cy,w,h,texid,angle;
    bool solid;
};

bool obj_solid(int texid) {
    switch(texid) {
        case 5:
        case 6:
        case 7:
        case 8:
            return 1;
        break;
        default: return 0; break;
    }
}

class _world {
    public:
        vector<struct buildings>b;
        _world() {b.clear();}
    void add(int x, int y, int texid, int angle) {
        struct buildings d;
        d.x=x; d.y=y; d.texid=texid;
        d.solid=obj_solid(texid);
        d.angle=angle;
        d.w=al_get_bitmap_width(tex_buildings[texid]);
        d.h=al_get_bitmap_height(tex_buildings[texid]);
        d.cx=d.w*0.5;
        d.cy=d.h*0.5;
        b.push_back(d);
    }
    int solid(int pos) {
        return b[pos].solid;
    }
    int find_(int x, int y) {
        for(int i=b.size()-1;i>=0;i--) {
            if(jCollPointRect(x,y,b[i].x,b[i].y,b[i].x+b[i].w,b[i].y+b[i].h)) {
                return i;
            }
        }
    }
    bool collide(int x, int y, int w, int h);
    void del(int pos);
    void draw(unsigned char id);
    void save();
    void load();
} world;

void _world::del(int pos) {
    b.erase(b.begin()+pos);
}
