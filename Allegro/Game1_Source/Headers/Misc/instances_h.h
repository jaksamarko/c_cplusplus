#define BULL_SIZ 3
#define BULL_SPD 20*GAME_SPD
#define BULL_DMG 50

#define BLOOD_TIME 400

#define P_UP_AMMO 0
#define P_UP_HEAL 1

class _view {
public:
    double x,y,w,h,xport,yport,wport,hport;
    ALLEGRO_BITMAP *b;
    _view() {x=y=w=h=xport=yport=wport=hport=0;b=NULL;}
}view[4];

class bullet {
    public:
        unsigned char owner;
        short int dmg;
		double x,y,dir;
		bool step();
		void draw(unsigned char index);
};

class item {
    public:
        int x,y,id,amount;
        void add(int x, int y, int id, int amount) {
            this->x=x;this->y=y;this->id=id;this->amount=amount;
        }
        void draw(unsigned char ind) {
            al_draw_scaled_bitmap(tex_item[id],0,0,al_get_bitmap_width(tex_item[id]),al_get_bitmap_height(tex_item[id]),x-view[ind].x,y-view[ind].y,32,32,0);
        }
};

class _bullets {
    public:
    vector<bullet> b;
    void create(double x, double y, double dir, unsigned char owner, weapon wep);
    void step();
    void draw(unsigned char index);
    void destroy(int pos);
    void start();
    _bullets() {start();}
}bullets;

class _blood {
	public:
	double x,y,angle;
	short int alpha,countdown,ind;
	_blood() {alpha=255;countdown=0;}
	bool step();
	void draw(unsigned char index);
};

class _bloods {
	public:
	vector<_blood> b;
	void create(double x,double y);
	void step();
	void draw(unsigned char index);
	void destroy(int pos);
	void start();
	_bloods() {start();}
}bloods;

class powups {
	public:
	double x,y; unsigned char type;
	void create(unsigned char type);
	void draw(unsigned char index);
};

class _pups {
	public:
	vector<powups>p;
	void spawn(double x, double y,unsigned char type);
	void draw(unsigned char index);
	void destroy(int pos);
	void start();
	_pups() {start();}
}powerups;

class _items {
    public:
        vector<item>it;
        _items() {it.clear();}
        void spawn(int x,int y, int id, int amount) {
            item tit;
            tit.add(x,y,id,amount);
            it.push_back(tit);
        }
        void destroy(int pos) {
            it.erase(it.begin()+pos);
        }
        void draw(unsigned char id) {
            for(int i=0;i<it.size();i++) {
                it[i].draw(id);
            }
        }
}items;

