#define CUTSCENE_H GAME_H*0.15
class scene {
    public:
        vector<char*>t;
        int ind;
        scene() {ind=0;t.clear();}
        void addText(char *text) {
            char *tmp=new char[strlen(text)+1];
            strcpy(tmp,text);
            this->t.push_back(tmp);
        }
        char* getText() {return t[ind];}
        bool next() {
            if(++ind==t.size()) {ind=0;return true;} else {return false;}
        }
};

class cutscene {
        ALLEGRO_COLOR col;
    public:
        int ind;
        float sz;
        vector<scene>s;
        void start() {
            //sz=0; ind=-1;
        }
        cutscene() {
            s.clear();
            start();
        }
        void add(int pos,char *text) {
            scene temp;
            if(pos>=s.size()) {
                s.push_back(temp);
            }
            s[pos].addText(text);
        }
        void play(int pos) {
            ind=pos;
            sz=0;
        }
        void step() {
            if(ind!=-1) {
                sz+=(CUTSCENE_H-sz)/5.; if(sz>CUTSCENE_H-2) {sz=CUTSCENE_H;}
            } else {
                sz-=(sz)/5.; if(sz<2) {sz=0;ind=-1;}
            }
        }
        void next() {
            ind=(s[ind].next())?-1:ind;
        }
        void draw() {
            if(sz>0) {
                al_draw_filled_rectangle(0,0,GAME_W,sz,al_map_rgb(0,0,0));
                al_draw_filled_rectangle(0,GAME_H-sz,GAME_W,GAME_H,al_map_rgb(0,0,0));
                if(sz==CUTSCENE_H&&ind!=-1) {
                    al_draw_text(font,al_map_rgb(255,255,255),GAME_W*0.5,GAME_H-sz*0.5,ALLEGRO_ALIGN_CENTRE,s[ind].getText());
                }
            }
        }
}cutscenes;
