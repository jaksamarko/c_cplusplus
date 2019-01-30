void vehicle::create(double x, double y, unsigned char type, unsigned char model, int id) {
	pass_cnt=0;
	driver=255;
	this->x=x;this->y=y;
	for(int i=0;i<4;i++) {pass[i]=V_NO_PASS;}
	switch(type) {
		case V_TYPE_CAR:
			switch(model) {
				case 0: pass_max=2; tex_id=0; handling=3.5; accel=1.3; maxspd=16; braking=0.7; xorig=48*5; yorig=23*5; break;
			}
		break;
	}
	w=al_get_bitmap_width(tex_vehicles[tex_id]);
	h=al_get_bitmap_height(tex_vehicles[tex_id]);
}
bool vehicle::free_seat() {return pass_cnt<pass_max;}
void vehicle::getin(unsigned char index) {for(int i=0;i<pass_max;i++) {if(pass[i]==V_NO_PASS) {pass[i]=index; break;}}pass_cnt++;}
void vehicle::getout(unsigned char index) {for(int i=0;i<pass_max;i++) {if(pass[i]==index) {pass[i]=V_NO_PASS;}}pass_cnt--;}
void vehicle::getin_driver(unsigned char index) {driver=index;}
void vehicle::getout_driver(unsigned char index) {driver=V_NO_PASS;}
double sign(double val) {if(val>0) {return 1;} if(val<0) {return -1;} return 0;}
double dabs(double val) {if(val<0) {val*=-1;} return val;}
void vehicle::handle(float h, float v) {
	v=ceil(v); h=ceil(h);
	if(v<0) {if(vspd<maxspd) {vspd+=accel;}}
	else if(v>0) {if(vspd>-(maxspd*0.25)) {vspd-=braking;}}
	dir-=h*handling*sign(vspd);
}

void vehicle::step() {
	vspd-=sign(vspd)*fmin(dabs(vspd),0.5);
	x+=jLengthdirX(vspd,dir);
	y+=jLengthdirY(vspd,dir);
	w=jLengthdirX(al_get_bitmap_width(tex_vehicles[tex_id]),dir);
	h=jLengthdirY(al_get_bitmap_height(tex_vehicles[tex_id]),dir);
}
void vehicle::draw(unsigned char index) {al_draw_scaled_rotated_bitmap(tex_vehicles[tex_id],xorig,yorig,x-view[index].x,y-view[index].y,0.2,0.2,DegToRad((-dir)),0);}

void _vehicles::start() {v.clear();}
void _vehicles::add(double x, double y, unsigned char type, unsigned char model) {
	vehicle t;
	t.create(x,y,type,model,id++);
	v.push_back(t);
}
int _vehicles::find(int id) {for(int i=0;i<v.size();i++) {if(v[i].id==id) {return i;}}}
void _vehicles::step() {for(int i=0;i<v.size();i++) {v[i].step();}}
void _vehicles::draw(unsigned char index) {for(int i=0;i<v.size();i++) {v[i].draw(index);}}
void _vehicles::destroy(int pos) {v.erase(v.begin()+pos);}
