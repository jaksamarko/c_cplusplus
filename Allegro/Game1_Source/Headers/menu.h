#define MENU_MAIN 0
#define MENU_PLAY 1
#define MENU_OPTION 2
#define MENU_CREDIT 3
char ***game_mode_texts,***players_texts;

const char menu_texts[10][2][25]={
	{//0
		{"Play"},
		{"Jatek"}
	},
	{//1
		{"Options"},
		{"Beallitasok"}
	},
	{//2
		{"Exit"},
		{"Kilepes"}
	},
	{//3
		{"Back"},
		{"Vissza"}
	},
	{//4
		{"Credits"},
		{"Keszitok"}
	},
	{//5
		{"Sounds"},
		{"Hangok"}
	},
	{//6
		{"Start"},
		{"Kezdes"}
	}
};

class _menu_button {
	public:
		int x,y,w,h,page,flags;
		void (*f)(void);
		char text[50],opt_cnt,curr_opt;
		char **options;
		bool lock,hover;
		float slide;
		ALLEGRO_COLOR col;
		_menu_button() {text[0]='\0';opt_cnt=curr_opt=0;options=NULL;}
};
class _menu_page {
	public:
		int id;
		vector<_menu_button> b;
		void add(_menu_button butt) {b.push_back(butt);}
};
class _menu {
	ALLEGRO_FONT *menufont;
	_menu_button b;
	void _add(int page, int x, int y, const char *text, void (*f)(void)) {
		int p_id=find_page(page);
		if(p_id==-1) {
			p.push_back(create(page));
			p_id=find_page(page);
		}
		b.x=x; b.y=y; b.f=f;
		b.col=col;
		strcpy(b.text,text);
		b.h=24;
		b.w=strlen(text)*18;
		b.options=NULL;
		b.curr_opt=b.opt_cnt=0;
	}
	int find_page(int page) {
		for(int i=0;i<p.size();i++) {
			if(p[i].id==page) {return i;}
		}
		return -1;
	}
	bool _open;
	ALLEGRO_COLOR col,col2;
	public:
	vector<_menu_page> p;
	int cp,w,h;
	_menu() {
		cp=0;
		_open=true;
		b.text[0]='\0';
	}
	void start() {cp=0;}
	void setfont(ALLEGRO_FONT *fnt,ALLEGRO_COLOR col, ALLEGRO_COLOR col2) {menufont=fnt;this->col=col;this->col2=col2;}
	void setsize(int w, int h) {this->w=w;this->h=h;}
	_menu_page create(int page) {
		_menu_page tmp_page;
		tmp_page.id=page;
		return tmp_page;
	}
	void add(int page, int x, int y, const char *text, void(*f)(void)) {
		_add(page,x,y,text,f);
		p[find_page(page)].add(b);
	}
	void add(int page, double x, double y, const char *text, void(*f)(void),bool lock) {
		_add(page,x,y,text,f);
		b.lock=lock;
		p[find_page(page)].add(b);
	}
	void add(int page, double x, double y, char **options, int options_cnt) {
		int p_id=find_page(page);
		if(p_id==-1) {p.push_back(create(page)); p_id=find_page(page);}
		b.x=x; b.y=y; b.f=NULL;
		b.col=col;
		b.options=options;
		b.opt_cnt=options_cnt;
		p[find_page(page)].add(b);
	}
	void setname(int page, int pos, char *text) {
		strcpy(p[find_page(page)].b[pos].text,text);
	}
	void add(int page, int x, int y, const char *text, void(*f)(void),float slide) {
		_add(page,x,y,text, f);
		b.slide=slide;
		p[find_page(page)].add(b);
	}
	void step() {
		_menu_button cb;
		int p_id=find_page(cp),msx=jMsX(w),msy=jMsY(h);
		msx=jMsX(w);
		msy=jMsY(h);
		if(p_id==-1) {return;}
		for(int i=0;i<p[p_id].b.size();i++) {
			p[p_id].b[i].hover=false;
			cb=p[p_id].b[i];
			if(jCollPointRect(msx,msy,cb.x,cb.y,cb.x+cb.w,cb.y+cb.h)) {
				p[p_id].b[i].hover=true;
				if(jMsP(MB_L)) {
					if(cb.opt_cnt>0) {
						p[p_id].b[i].curr_opt=(cb.curr_opt+1)%cb.opt_cnt;
					} else {
						cb.f();
					}
				}
			}
		}
		if(jKbP(ALLEGRO_KEY_ESCAPE)) {

		}
	}
	bool opened() {return _open;}
	void close() {_open=false;}
	void open() {_open=true;}
	void draw() {
		char *tmp_text;
		_menu_button cb;
		int p_id=find_page(cp);
		if(p_id==-1) {return;}
		al_clear_to_color(al_map_rgb(0,0,0));
		for(int i=0;i<p[p_id].b.size();i++) {
			cb=p[p_id].b[i];
			tmp_text=(cb.opt_cnt==0)?(cb.text):cb.options[cb.curr_opt];
			al_draw_text(menufont,(cb.hover==true)?col2:col,cb.x,cb.y,0,tmp_text);
		}
		al_flip_display();
	}
	void setpage(int page) {cp=page;}
	int get(int page, int pos) {
		_menu_button cb;
		page=find_page(page);
		cb=p[page].b[pos];
		if(cb.opt_cnt) {
			return cb.curr_opt;
		}
		return 0;
	}
}menu;
