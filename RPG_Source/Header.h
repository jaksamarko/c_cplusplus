#pragma once
#include<vector>
#include<string>

using namespace std;

double distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

class quest {
public:
	string name, descr;
	int minLvl;
	float rewXp;
	quest *n;
	vector<Task>tasks;
	vector<Item>rewIt;
};

class Npc : public Entity {

};


struct Task {
public:
	string descr;
	virtual bool completed() {
		return true;
	}
};

struct taskTalk : public Task {
	Entity *npcId;
	string completeText;
	bool completed() { 
	}
};

struct taskTravel : public Task {
	double locX, locY;
	taskTravel(double inlocX, double inlocY) : locX(inlocX), locY(inlocY) {

	}
	bool completed(Player *p) {
		return distance(p.getX(), p.getY(), locX, locY)<32;
	}
};

class Entity {
protected:
	int sprIndex;
	float hp, crit, dmg, def, xp, xpNext, x, y;
	int stam, agil, strg, prot, lvl;
	Entity(int sStam = 0, int sAgil = 0, int sStrg = 0, int sProt = 0, int sLvl = 1) : stam(sStam), agil(sAgil), strg(sStrg), prot(sProt), lvl(sLvl) {
		hp = crit = dmg = def = xp = xpNext = x = y = 0;

		updateValues();
		sprIndex = -1;

		x = 0;
		y = 0;
	}
	void updateValues() {
		hp = 100 * (1 + stam / 10. + lvl / 15);
		crit = 100 - 30 - 60 / (1 + agil / 5 + lvl / 10);
		def = 1 * (1 + prot / 12 + lvl / 15);
		dmg = 1 * (1 + strg / 12 + lvl / 15);

		while (xp >= xpNext) {
			xp -= xpNext;
			xpNext = log(lvl / 2.0 + 1)*(100 + lvl);
		}
	}

public:
	void defaultDraw() {
		spriteList.draw(sprIndex, x, y);
		draw();
	}
	virtual void draw() {
	}

	void move(float xAdd, float yAdd, float spd) {
		this->x += xAdd * spd;
		this->y += yAdd * spd;
	}
	void setSprite(int ind) {
		sprIndex = ind;
	}
	float getX() { return x; }
	float getY() { return y; }
};

class Item {
	uint16_t id;
	uint8_t num;
	vector<int>attr;
public:
	Item(int setId = -1, int amount = 1) : id(setId), num(amount)  {

	}
};

class Player : public Entity {
	Item inv[10];
public:
	Player() {
		x = 0;
		y = 0;
	}
};
class Enemy : public Entity {

};