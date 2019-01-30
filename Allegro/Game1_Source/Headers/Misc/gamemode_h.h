#define GM_CAMPAIGN 0
#define GM_SURVIVAL 1
#define GM_VERSUS 2
#define GM_WAVE 3
#define GM_NEMESYS 4

#define WAVE_START 0
#define WAVE_DURING 1
#define WAVE_END 2

class _gamecontrol {
	bool ready[4];
	public:
	int timer,quest;
	char gm,wave,mission,nemesys;
	_gamecontrol() {}
	void start();
	void step();
	void setgm(char mode);
	void draw();
}gm;
