bool bullet::step() {
	x+=jLengthdirX(BULL_SPD,dir);
    y+=jLengthdirY(BULL_SPD,dir);
	return false;
}
void bullet::draw(unsigned char index) {
	al_draw_filled_circle(x-view[index].x,y-view[index].y,BULL_SIZ,al_map_rgba(0,0,0,255));
}

void _bullets::create(double x, double y, double dir, unsigned char owner, weapon p_wep) {
    bullet t; t.x=x; t.y=y; t.dir=dir; t.owner=owner; t.dmg=p_wep.dmg; b.push_back(t);
}
void _bullets::start() {b.clear();}
void _bullets::step() {for(int i=0;i<b.size();i++) {if(b[i].step()) {destroy(i);}}}
void _bullets::draw(unsigned char index) {for(int i=0;i<b.size();i++) {b[i].draw(index);}}
void _bullets::destroy(int pos) {b.erase(b.begin()+pos);}

bool _blood::step() {
	countdown++;
	if(countdown>BLOOD_TIME) {
		alpha-=1./globalfps;
		if(alpha<=0) {return true;}
	}
	return false;
}
void _blood::draw(unsigned char index) {
	al_draw_tinted_scaled_rotated_bitmap(tex_blood[ind],al_map_rgba(alpha,alpha,alpha,alpha),64,64,x-view[index].x,y-view[index].y,0.35,0.35,DegToRad(-angle),0);
}

void _bloods::start() {b.clear();}
void _bloods::create(double x, double y) {
	_blood tmp;
	tmp.x=x; tmp.y=y; tmp.angle=rand()%360; tmp.ind=rand()%2;
	b.push_back(tmp);
}
void _bloods::step() {for(int i=0;i<b.size();i++) {if(b[i].step()){destroy(i);}}}
void _bloods::destroy(int pos) {b.erase(b.begin()+pos);}
void _bloods::draw(unsigned char index) {for(int i=0;i<b.size();i++) {b[i].draw(index);}}

void powups::draw(unsigned char index) {
	al_draw_scaled_bitmap(tex_powups[type],0,0,al_get_bitmap_width(tex_powups[type]),al_get_bitmap_height(tex_powups[type]),x-view[index].x,y-view[index].y,32,32,0);
}
void _pups::start() {p.clear();}
void _pups::spawn(double x, double y,unsigned char type) {
	powups ptemp;
	ptemp.x=x; ptemp.y=y; ptemp.type=type;
	p.push_back(ptemp);
}
void _pups::draw(unsigned char index) {for(int i=0;i<p.size();i++) {p[i].draw(index);}}
void _pups::destroy(int pos) {p.erase(p.begin()+pos);}
