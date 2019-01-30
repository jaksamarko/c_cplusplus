#define INV_SIZE 25
#define INV_GRID_W 5
#define MAX_STACK 15

class inv_slot {
    public:
        int id,amount;
        inv_slot() {id=-1;amount=0;}
};

class inventory {
        inv_slot inv[INV_SIZE];
        bool put(int ind, item *it) {
            int t_amount=fmin(MAX_STACK-inv[ind].id,it->amount);
            it->amount-=t_amount;
            inv[ind].id=it->id;
            inv[ind].amount+=t_amount;
            return (it->amount==0);
        }
    public:
        bool show;
        inventory() {show=false;}
        void pickup(int pos) {
            bool done=false,full=true;
            item *it=&items.it[pos];
            for(int i=0;i<INV_SIZE;i++) {
                if(inv[i].id==it->id) {
                    done=put(i,it); if(done) {break;}
                }
            }
            while(!done) {
                full=true;
                for(int i=0;i<INV_SIZE;i++) {
                    if(inv[i].id==-1) {
                        full=false;
                        done=put(i,it); if(done) {break;}
                    }
                }
                if(full) {break;}
            }
            if(done) {items.destroy(pos);}
        }
        void draw(unsigned char id) {
            if(show) {
                for(int i=0;i<INV_SIZE/INV_GRID_W;i++) {
                    for(int j=0;j<INV_GRID_W;j++) {
                        al_draw_bitmap(tex_gui[0],view[id].xport+j*68,view[id].yport+i*68,0);
                        if(inv[i*INV_GRID_W+j].id!=-1) {
                            al_draw_bitmap(tex_item[inv[i*INV_GRID_W+j].id],view[id].xport+j*68+2,view[id].yport+i*68+2,0);
                            al_draw_textf(font,al_map_rgb(0,0,255),view[id].xport+j*68+34,view[id].yport+i*68+34,0,"%d",inv[i*INV_GRID_W+j].amount);
                        }
                    }
                }
            }
        }
};
