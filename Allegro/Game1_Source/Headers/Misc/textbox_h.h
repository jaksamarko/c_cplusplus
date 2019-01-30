#define MAX_LENGTH 32
#define T_SPD 6
class textBox {
        int timer;
        uint16_t w,h,x,y;
        char *text,*ttext,l;
        void partText(int start,int length) {
            char pos=0;
            for(int i=0;i<length;i++) {
                this->ttext[i]=this->text[i+start];
                if(ttext[i]=='\0'||i==MAX_LENGTH-1) {pos=i;break;}
            }
            ttext[pos]='\0';

        }
    public:
        bool show;
        textBox() {
            show=x=y=w=h=l=0;text=NULL;
            ttext=new char[MAX_LENGTH+1];
            ttext[MAX_LENGTH]='\0';
        }
        void spawn(char *text) {
            this->text=new char[strlen(text)+1]; strcpy(this->text,text);
            show=true;timer=true;
            partText(0,MAX_LENGTH);
            w=al_get_text_width(font,ttext)+10;
            l=strlen(text)/MAX_LENGTH+(strlen(text)%MAX_LENGTH>0);
            h=al_get_font_line_height(font)*l+10;
            x=(GAME_W-w)*0.5;y=(GAME_H-h)*0.75;
            timer=0;
        }
        void step() {
            timer++;
        }
        void draw() {
            if(show) {
                al_draw_rectangle(x,y,x+w,y+h,al_map_rgb(255,0,0),2);
                for(int i=0;i<l;i++) {
                    partText(MAX_LENGTH*i,/*timer/(globalfps/T_SPD)*/100);
                    al_draw_text(font,al_map_rgb(0,255,0),GAME_W*0.5,y+5+i*al_get_font_line_height(font),ALLEGRO_ALIGN_CENTRE,ttext);
                }
            }
        }
        void close() {
            show=false;
            delete[] this->text;
        }
}tBox;
