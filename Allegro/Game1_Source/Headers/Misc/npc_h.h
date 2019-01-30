class npc {
    public:
        void (*real_action)(npc *n);
        int x,y,skin;
        bool have_quest,quest_accepted;
        char *name,tind;
        npc() {x=y=skin=have_quest=quest_accepted=0;tind=-1;name=NULL;real_action=NULL;}
        void draw(unsigned char id) {
            al_draw_scaled_rotated_bitmap(tex_player[0][0],32,32,x-view[id].x,y-view[id].y,0.35,0.35,0,0);
        }
        bool action() {
            tind++;
            real_action(this);
            if(tind==-1) {tBox.close(); return true;}
            return false;
        }
};

class _npcs {
    public:
        vector<npc>n;
        _npcs() {n.clear();}
        void create(int x, int y, int skin, char *name, void(*action)(npc *n)) {
            npc t;
            t.x=x;t.y=y;t.skin=skin;t.name=new char[strlen(name)+1];strcpy(t.name,name);t.real_action=action;
            n.push_back(t);
        }
        /*
        int found(char *name) {
            for(int i=0;i<;i++) {if(strcmp(n[i].name,name)==0) {return i;}}
        }*/
        void draw(unsigned char id) {
            for(int i=0;i<n.size();i++) {n[i].draw(id);}
        }

}npcs;
