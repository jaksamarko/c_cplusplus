#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

#define TARGET_FPS 60

#define MAP_DEFAULT_SIZE 32
class SDLframeWork {
public:
	SDL_Window *win;
	SDL_Renderer *render;
	SDL_Surface *wSurface;

	map<int, bool>keys;

	SDLframeWork(const char *wName = "", int width = 640, int height = 480) {
		try {
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
				throw runtime_error(SDL_GetError());
			}
			if (!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)) {
				throw runtime_error(IMG_GetError());
			}
		}
		catch (exception& e) {
			cout << e.what();
		}

		win = SDL_CreateWindow(wName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
		render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		wSurface = SDL_GetWindowSurface(win);

		SDL_RenderSetScale(render, 2, 2);
	}
	~SDLframeWork() {
		
	}
	bool getKey(int key) {
		if (keys.find(key) != keys.end()) {
			return keys[key];
		}
		return false;
	}
	void setKey(int key, bool state) {
		if (keys.find(key) == keys.end()) {
			keys.emplace(key, state);
		}
		else {
			keys[key] = state;
		}
	}
	void run(void(*extStart)(),bool(*extLoop)()) {
		uint64_t then = 0,sec=SDL_GetTicks(),fps=0;
		SDL_Event ev;
		bool exitLoop = false;
		extStart();
		cout << "Ext start done!" << endl;
		while (!exitLoop) {
			while (SDL_PollEvent(&ev)) {
				switch (ev.type) {
					case SDL_KEYDOWN:
						setKey(ev.key.keysym.sym, true);
						break;
					case SDL_KEYUP:
						setKey(ev.key.keysym.sym, false);
						break;
				}
			}
			fps++;
			exitLoop=extLoop();
			SDL_RenderPresent(render);
			SDL_Delay(fmax(0,1000 / TARGET_FPS - (SDL_GetTicks() - then)));
			then = SDL_GetTicks();
			if ((then - sec) >= 1000) {
				cout << fps << endl;
				fps = 0;
				sec = SDL_GetTicks();
			}
		}
	}
};
SDLframeWork *fw;

SDL_Texture *loadTexture(char *fname) {
	SDL_Surface *loadSurf = IMG_Load(fname), *optSurf = NULL;
	SDL_Texture *tex = NULL;
	try {
		if (loadSurf == NULL) {
			throw runtime_error(IMG_GetError());
		}
		else {
			optSurf = SDL_ConvertSurface(loadSurf, fw->wSurface->format, NULL);
			SDL_FreeSurface(loadSurf);
			if (optSurf == NULL) {
				throw runtime_error(SDL_GetError());
			}
			tex = SDL_CreateTextureFromSurface(fw->render,optSurf);
		}
	}
	catch (exception& e) {
		cout << e.what();
	}
	return tex;
}

struct GameMap {
	SDL_Texture *tileset;
	int **data, tileSize,texSize;
	bool load(const char *fnameTile, const char *fnameMap, int tileSize,int tileSpacing) {
		tileset = loadTexture((char*)fnameTile);
		if (tileset == NULL) {
			return false;
		}
		ifstream inf(fnameMap);
		data = new int*[MAP_DEFAULT_SIZE];
		for (auto i = 0; i < MAP_DEFAULT_SIZE; i++) {
			data[i] = new int[MAP_DEFAULT_SIZE];
			for (auto j = 0; j < MAP_DEFAULT_SIZE; j++) {
				data[i][j] = 5;
			}
		}
		this->tileSize = tileSize;
		this->texSize = tileSize + tileSpacing;
		return true;
	}
	void drawTile(int x, int y, int id) {
		SDL_Rect srcR = { (id % MAP_DEFAULT_SIZE)*texSize, (id / MAP_DEFAULT_SIZE)*texSize, tileSize, tileSize },
			destR = { x,y,tileSize,tileSize };
		SDL_RenderCopy(fw->render, tileset, &srcR, &destR);
	}

	void drawMap(float x, float y) {
		int w=fw->wSurface->w, h=fw->wSurface->h;
		for (int i = fmax(0,x-w*.5); i < fmin(w+x,MAP_DEFAULT_SIZE*tileSize); i += tileSize) {
			for (int j = fmax(0,y-h*.5); j < fmin(h+y,MAP_DEFAULT_SIZE*tileSize); j += tileSize) {
				drawTile(i-x, j-y, data[i / tileSize][j / tileSize]);
			}
		}
	}
};

struct SpriteList {
	typedef struct Sprite {
		SDL_Texture *tex;
		int w, h;
	}Sprite;
	vector<Sprite>list;
	Sprite operator[](int i){
		return list[i];
	}
	int load(const char *fname) {
		Sprite spr;
		spr.tex = loadTexture((char*)fname);
		SDL_QueryTexture(spr.tex,NULL,NULL,&spr.w,&spr.h);
		list.push_back(spr);
		return list.size() - 1;
	}

	void draw(int index, float x, float y) {
		if (index != -1) {
			SDL_Rect src = { 0, 0, list[index].w, list[index].h }, dest = { x,y,list[index].w, list[index].h };
			SDL_RenderCopy(fw->render, list[index].tex, &src, &dest);
		}
	}
};
SpriteList spriteList;

#include "Header.h"

GameMap gameMap;
Player player;
vector<Entity*> entities;


void gameStart() {
	gameMap.load("rtile.png", "map.csv", 16,1);
	player.setSprite(spriteList.load("player.png"));
	spriteList.load("monster.png");

	entities.push_back(&player);
}

bool gameLoop() {
	if (fw->getKey(SDLK_ESCAPE)) {
		return true;
	}

	player.move(fw->getKey(SDLK_d)-fw->getKey(SDLK_a),fw->getKey(SDLK_s)-fw->getKey(SDLK_w),1);
	gameMap.drawMap(player.getX(),player.getY());
	for (auto i = entities.begin(); i != entities.end(); i++) {
		(*i)->defaultDraw(); 
	}
	
	return false;
}

int main(int argc, char * argv[])
{
	fw = new SDLframeWork();
	try {
		fw->run(&gameStart,&gameLoop);
	}
	catch (exception &e) {
		cout << e.what();
	}

	return 0;
}