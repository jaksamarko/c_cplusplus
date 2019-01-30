#define CONTR_KEYB1 0
#define CONTR_KEYB2 1
#define CONTR_JOY1 2
#define CONTR_JOY2 3
#define CONTR_JOY3 4
#define CONTR_JOY4 5

#define PLA_SPD 4*GAME_SPD

class _p {
    vehicle *t_v;
    inventory inv;
    _editor editor;
	public:
    double lastx,lasty,x,y,anim,dir,ind,hspd,vspd,shoot_dir;
    bool reload_button,shoot_button,act1_bt,act_bt[4],incar,drive;
    short int hp,rtime,stime,kill_cnt,w,h; char wp_pos,contr_type,id;
    int v_id,n_id;
    weapon wp[3];
    _p() {lastx=lasty=x=y=anim=dir=wp_pos=ind=rtime=stime=incar=drive=kill_cnt=contr_type=0;v_id=n_id=-1;hp=100;w=66*0.35;h=66*0.35;}
    void step();
    void draw();
    bool nemesys();
    void draw_gui();
};

class _players {
	public:
		_p p[4];
		unsigned char cnt;
		_players() {cnt=4;for(int i=0;i<4;i++) {p[i].id=i;}}
		void set_contr(char index, char contr_type);
		void step();
		void draw(unsigned char index);
		void draw_gui();
}players;
