void _gamecontrol::setgm(char mode) {this->gm=mode;}

void _gamecontrol::step() {
	bool all_ready=true;
	switch(gm) {
		case GM_CAMPAIGN:
		break;
		case GM_SURVIVAL:
			if(timer<=0) {
                wave=WAVE_DURING;
				for(int i=0;i<4;i++) {mobs.spawn(MOB_ZOMBIE,players.p[i%players.cnt].x+rand()%1024-512,players.p[i%players.cnt].y+rand()%1024-512);}
				timer=10*globalfps;
			}
		break;
		case GM_WAVE:
            if(wave==WAVE_DURING) {
                if(mobs.mob.size()==0) {wave=WAVE_END;}
            } else {
                for(int i=0;i<players.cnt;i++) {
                    if(players.p[i].act_bt[2]) {ready[i]=true;}
                    if(!ready[i]) {all_ready=false; break;}
                }
                if(all_ready) {
                    mobs.spawn(MOB_ZOMBIE,players.p[0].x+rand()%1024-512,players.p[0].y+rand()%1024-512);
                    for(int i=0;i<players.cnt;i++) {ready[i]=false;}
                    wave=WAVE_DURING;
                }
            }
        break;
		case GM_NEMESYS:
            if(timer<=0) {
                nemesys=rand()%players.cnt;
                wave=WAVE_DURING;
            }
		break;
		case GM_VERSUS:
		    if(timer<=0) {
                wave=WAVE_DURING;
		    }
		break;
	}
	if(timer>0) {timer--;}
}

void _gamecontrol::start() {
    wave=WAVE_START;
    nemesys=quest=-1;
    switch(gm) {
        case GM_CAMPAIGN:
            mission=0;
            timer=0;
            quest=0;
            //cutscenes.play(0);
        break;
        case GM_SURVIVAL:
            timer=5*globalfps;
        break;
        case GM_WAVE:
            timer=3*globalfps;
            for(int i=0;i<4;i++) {ready[i]=false;}
        break;
        case GM_NEMESYS:
            nemesys=-1;
            timer=10*globalfps;
        break;
        case GM_VERSUS:
            timer=5*globalfps;
        break;
    }
}

void _gamecontrol::draw() {
    if(timer>=0&&WAVE_START) {
        al_draw_textf(font,al_map_rgb(220,0,0),400,225,ALLEGRO_ALIGN_CENTRE,"%d",int(timer/globalfps+1));
    }
}
