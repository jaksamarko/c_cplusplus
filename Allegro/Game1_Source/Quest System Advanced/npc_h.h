class npc {
    public:
        vector<*quest>q;
        int x,y,skin;
        char *name;
        npc() {x=y=skin=0;name=NULL;q.clear();}
};

class _npcs {
        vector<npc>n;
    public:
        _npcs() {n.clear();}
        void create(int x, int y, int skin, char *name) {
            npc t;
            t.x=x;t.y=y;t.skin=skin;strcpy(t.name,name);
            n.push_back(t);
        }
        int found(char *name) {
            for(int i=0;i<;i++) {if(strcmp(n[i].name,name)==0) {return i;}}
        }
        void draw(unsigned char index) {
            //al_draw_bitmap();
        }

}npcs;
