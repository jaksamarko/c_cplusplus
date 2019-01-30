#define VEHICLES_COUNT 1
#define V_NO_PASS 255
#define V_TYPE_CAR 0

class vehicle {
	public:
		double x,y,w,h,dir,spd,handling,accel,maxspd,vspd,hspd,braking;
		int id,xorig,yorig;
		unsigned char type,model,pass_cnt,pass_max,pass[4],tex_id,driver;
		void create(double x, double y, unsigned char type, unsigned char model, int id);
		bool free_seat();
		void getin(unsigned char index);
		void getout(unsigned char index);
		void getin_driver(unsigned char index);
		void getout_driver(unsigned char index);
		void handle(float h, float v);
		void step();
		void draw(unsigned char index);
};

class _vehicles {
	int id;
	public:
		vector<vehicle> v;
		void start();
		_vehicles() {id=0;start();}
		void add(double x, double y, unsigned char type, unsigned char model);
		int find(int id);
		void step();
		void draw(unsigned char index);
		void destroy(int pos);
}vehicles;
