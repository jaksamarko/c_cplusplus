void _mob::setspr() {
	switch(type) {
        case MOB_ZOMBIE:
            spr=tex_zombie[anim_type];
            switch(anim_type) {
                case MOB_ZOMBIE_STAND: anim_cnt=1; break;
                case MOB_ZOMBIE_RUN: anim_cnt=8; break;
                case MOB_ZOMBIE_DIE: anim_cnt=5; break;
                case MOB_ZOMBIE_HURT: anim_cnt=5; break;
                case MOB_ZOMBIE_DIE2: anim_cnt=8; break;
                case MOB_ZOMBIE_ATTACK: anim_cnt=6; break;
            }
        break;
    }
}

void _mob::create(short int type,double x, double y) {
    this->type=type;
    this->x=this->lastx=x;
    this->y=this->lastx=y;
    setspr();
    switch(type) {
        case MOB_ZOMBIE:
        break;
    }
}

bool _mob::step() {
    double temp_dist;
    vehicle tmp_v;
    if(die) {
    	targetp=-1;
    	if(anim_type!=MOB_ZOMBIE_DIE&&anim_type!=MOB_ZOMBIE_DIE2) {
    		ind=0;
			anim_type=MOB_ZOMBIE_DIE;
		}
		if(ind>=anim_cnt-1) {
				anim=0;
				countdown+=1./globalfps;
				if(countdown>1) {
					alpha-=255./globalfps;
					if(alpha<=0) {return true;}
				}
			}
	} else {
	    attack_timer-=(attack_timer>=0);
		for(int i=0;i<vehicles.v.size();i++) {
			tmp_v=vehicles.v[i];
			if(jCollRectRect(x,y,w,h,tmp_v.x,tmp_v.y,tmp_v.w,tmp_v.h)) {
				vehicles.destroy(i);
			}
		}
		for(int i=0;i<bullets.b.size();i++) {
			if(jDistance(x,y,bullets.b[i].x,bullets.b[i].y)<w) {
				hp-=bullets.b[i].dmg;
				hurt=true;
				anim_type=MOB_ZOMBIE_HURT; ind=0;
				bloods.create(x,y);
				if(hp<=0) {
					players.p[bullets.b[i].owner].kill_cnt++;
					die=true;
				}
				bullets.destroy(i);
			}
		}
		if(hurt) {
			anim=1/5.*GAME_SPD;
			if(ind>anim_cnt) {hurt=false;}
		} else {
			spd=MOB_SPD*(targetp!=-1);
			if(targetp==-1||jDistance(players.p[targetp].x,players.p[targetp].y,x,y)>FOLLOW_DIST) {
		        targetp=-1;
		        for(int i=0;i<players.cnt;i++) {
		            if(jDistance(players.p[i].x,players.p[i].y,x,y)<FOLLOW_DIST) {
		                targetp=i; break;
		            }
		        }
		        if(targetp==-1) {anim=0;anim_type=MOB_ZOMBIE_STAND;}
		    } else {
		        anim=1/5.*GAME_SPD;
		        lastx=x;
		        lasty=y;
		        dir=jDirection(x,y,players.p[targetp].x,players.p[targetp].y);
		        temp_dist=jDistance(x,y,players.p[targetp].x,players.p[targetp].y);
		        if(temp_dist>32) {
                    if(attack_timer<=0) {
                        x+=jLengthdirX(spd,dir);
                        y+=jLengthdirY(spd,dir);
                        anim_type=MOB_ZOMBIE_RUN;
                    }
		        } else {
		            anim_type=MOB_ZOMBIE_ATTACK;
		            if(attack_timer<=0) {
                        attack_timer=globalfps*2;
                        players.p[targetp].hp-=20;
		            }
		        }
		    }
		}
	}
    ind+=anim;
    setspr();
    return false;
}

void _mob::draw(unsigned char index) {
	al_draw_tinted_scaled_rotated_bitmap(spr[int(ind)%anim_cnt],al_map_rgba(alpha,alpha,alpha,alpha),64,64,x-view[index].x,y-view[index].y,0.35,0.35,DegToRad(-dir),0);
	if(!die) {
    	al_draw_filled_rectangle(x-view[index].x,y-view[index].y-h*1,x-view[index].x+w,y-view[index].y-h*0.8,al_map_rgba(255,0,0,255));
    	al_draw_filled_rectangle(x-view[index].x,y-view[index].y-h*1,x-view[index].x+w*hp/100.,y-view[index].y-h*0.8,al_map_rgba(0,255,0,255));
	}
}

void _mobs::start() {
    mob.clear();
}

void _mobs::spawn(short int type, double x, double y) {
	_mob temp_mob;
    temp_mob.type=type; temp_mob.x=x; temp_mob.y=y; temp_mob.anim_type=0; temp_mob.setspr();
    switch(type) {
    	case MOB_ZOMBIE: temp_mob.w=al_get_bitmap_width(tex_zombie[0][0])*0.35;temp_mob.h=al_get_bitmap_height(tex_zombie[0][0])*0.35; break;
	}
    mob.push_back(temp_mob);
}
void _mobs::step() {for(int i=0;i<mob.size();i++) {if(mob[i].step()) {destroy(i);}}}
void _mobs::draw(unsigned char index) {for(int i=0;i<mob.size();i++) {mob[i].draw(index);}}
void _mobs::destroy(int pos) {mob.erase(mob.begin()+pos);}

