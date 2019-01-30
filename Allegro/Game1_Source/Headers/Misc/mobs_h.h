#define FOLLOW_DIST 1024
#define MOB_SPD 3*GAME_SPD

#define MOB_ZOMBIE 0

#define MOB_ZOMBIE_STAND 0
#define MOB_ZOMBIE_RUN 1
#define MOB_ZOMBIE_DIE 2
#define MOB_ZOMBIE_DIE2 3
#define MOB_ZOMBIE_HURT 4
#define MOB_ZOMBIE_ATTACK 5

class _mob {
    public:
    double lastx,lasty,x,y,anim,dir,ind,anim_start_ind,spd,alpha,countdown;
    int targetp,w,h;
    ALLEGRO_BITMAP **spr;
    short int hp,type,anim_type,anim_cnt,attack_timer;
    bool die,hurt;
    _mob() {lastx=lasty=x=y=anim=attack_timer=dir=ind=spd=anim_start_ind=countdown=0;alpha=255;targetp=-1;die=hurt=false;hp=100;spr=NULL;}
    void create(short int type,double x, double y);
    bool step();
    void draw(unsigned char index);
    void setspr();
    void start();
};

class _mobs {
    public:
    vector<_mob> mob;
    void spawn(short int type, double x, double y);
    void step();
    void draw(unsigned char index);
    void destroy(int pos);
    void hurt(bullet b, int pos);
    void start();
    _mobs() {start();}
}mobs;
