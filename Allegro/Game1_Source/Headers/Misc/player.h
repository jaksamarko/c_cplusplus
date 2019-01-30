bool _p::nemesys() {
    return (gm.nemesys==id);
}

void _p::step() {
    int tmp_b_cnt,t_joy;
    lastx=x; lasty=y;
    if(hp<=0) {
        printf("Kurva anyad!!");
        exit(0);
    }
    editor.step(id);
    switch(contr_type) {
    	case CONTR_KEYB1:
			hspd=(jKbB(ALLEGRO_KEY_D)-jKbB(ALLEGRO_KEY_A));
    		vspd=(jKbB(ALLEGRO_KEY_S)-jKbB(ALLEGRO_KEY_W));
    		reload_button=jKbP(ALLEGRO_KEY_R);
    		shoot_button=jMsB(MB_L);
    		act_bt[0]=jKbP(ALLEGRO_KEY_E);
			act_bt[1]=jKbP(ALLEGRO_KEY_F);
    		act_bt[2]=jKbP(ALLEGRO_KEY_G);
    		act_bt[3]=jKbP(ALLEGRO_KEY_I);
		break;
		case CONTR_KEYB2:
			hspd=(jKbB(ALLEGRO_KEY_RIGHT)-jKbB(ALLEGRO_KEY_LEFT));
    		vspd=(jKbB(ALLEGRO_KEY_DOWN)-jKbB(ALLEGRO_KEY_UP));
    		reload_button=jKbP(ALLEGRO_KEY_PAD_0);
    		shoot_button=jKbB(ALLEGRO_KEY_PAD_7)+jKbP(ALLEGRO_KEY_PAD_8)+jKbP(ALLEGRO_KEY_PAD_9)+jKbP(ALLEGRO_KEY_PAD_4)+jKbP(ALLEGRO_KEY_PAD_6)+jKbP(ALLEGRO_KEY_PAD_1)+jKbP(ALLEGRO_KEY_PAD_2)+jKbP(ALLEGRO_KEY_PAD_3);
		break;
		default:
			t_joy=contr_type-CONTR_JOY1;
			hspd=round(jJoyA(t_joy,0,0));
			vspd=round(jJoyA(t_joy,0,1));
			reload_button=jJoyP(t_joy,4);
			shoot_button=jJoyB(t_joy,5);
			for(int i=0;i<3;i++) {act_bt[i]=jJoyP(t_joy,i);}
		break;
	}
	if(incar) {
		t_v=&vehicles.v[vehicles.find(v_id)];
		x=t_v->x; y=t_v->y;
		if(drive) {
			t_v->handle(hspd,vspd);
		}
	} else {
		y+=(vspd)*PLA_SPD;
        x+=(hspd)*PLA_SPD;
        if(world.collide(x,lasty,w,h)) {x=lastx;}
        if(world.collide(lastx,y,w,h)) {y=lasty;}
        if(lastx!=x||lasty!=y) {
            anim=1/5.*GAME_SPD;
            dir=jDirection(0,0,x-lastx,y-lasty);
        } else {
            ind=0;
            anim=0;
        }
        for(int i=0;i<powerups.p.size();i++) {
        	if(jCollRectRect(x,y,w,h,powerups.p[i].x,powerups.p[i].y,32,32)) {
        		switch(powerups.p[i].type) {
        			case P_UP_AMMO:
        				if(wp[wp_pos].ammo<wp[wp_pos].maxammo||wp[wp_pos].ammopack<wp[wp_pos].maxammopack) {
        					wp[wp_pos].ammo=wp[wp_pos].maxammo;
        					wp[wp_pos].ammopack=wp[wp_pos].maxammopack;
							powerups.destroy(i);
						}
					break;
				}

			}
		}
        ind+=anim*GAME_SPD;
	}
    view[id].x=x-view[id].w*0.5;
    view[id].y=y-view[id].h*0.5;
    if(reload_button) {
        if(rtime<0) {
            tmp_b_cnt=fmin(wp[wp_pos].ammopack,wp[wp_pos].maxammo-wp[wp_pos].ammo);
            wp[wp_pos].ammo+=tmp_b_cnt;
            wp[wp_pos].ammopack-=tmp_b_cnt;
            rtime=wp[wp_pos].reload_time;
        }
    }
    if(shoot_button) {
    	if(wp[wp_pos].ammo>0) {
    		if(rtime<0&&stime<0) {
	        	switch(contr_type) {
	        		case CONTR_KEYB1: shoot_dir=jDirection(view[id].xport+view[id].w*0.5,view[id].yport+view[id].h*0.5,jMsX(view[id].w),jMsY(view[id].h)); break;
	        		case CONTR_KEYB2:
						if(jKbP(ALLEGRO_KEY_PAD_6)) {shoot_dir=0;}
						if(jKbP(ALLEGRO_KEY_PAD_9)) {shoot_dir=45;}
						if(jKbP(ALLEGRO_KEY_PAD_8)) {shoot_dir=90;}
						if(jKbP(ALLEGRO_KEY_PAD_7)) {shoot_dir=135;}
						if(jKbP(ALLEGRO_KEY_PAD_4)) {shoot_dir=180;}
						if(jKbP(ALLEGRO_KEY_PAD_1)) {shoot_dir=225;}
						if(jKbP(ALLEGRO_KEY_PAD_2)) {shoot_dir=270;}
						if(jKbP(ALLEGRO_KEY_PAD_3)) {shoot_dir=315;}
					break;
					case CONTR_JOY1:
					case CONTR_JOY2:
					case CONTR_JOY3:
					case CONTR_JOY4:
						t_joy=contr_type-CONTR_JOY1;
						shoot_dir=jDirection(0,0,jJoyA(t_joy,1,0),jJoyA(t_joy,1,1));
					break;
				}
	            bullets.create(x,y,shoot_dir,id,wp[wp_pos]);
	            stime=wp[wp_pos].shoot_time;
	            wp[wp_pos].ammo--;
	        }
		}
    }
    if(act_bt[0]) {
        if(cutscenes.ind!=-1) {
            cutscenes.next();
        } else {
            for(int i=0;i<items.it.size();i++) {
                if(jDistance(x,y,items.it[i].x,items.it[i].y)<32) {
                    inv.pickup(i);
                }
            }
        }

    }
    if(act_bt[1]) {
		if(incar) {
			if(drive) {
				vehicles.v[vehicles.find(v_id)].getout_driver(id);
			} else {
				vehicles.v[vehicles.find(v_id)].getout(id);
			}
			incar=false;drive=true;
		} else {
		    if(n_id==-1) {
                for(int i=0;i<npcs.n.size();i++) {
                    if(jDistance(x,y,npcs.n[i].x,npcs.n[i].y)<40) {
                        npcs.n[i].action();
                        n_id=i;
                    }
                }
                for(int i=0;i<vehicles.v.size();i++) {
                    if(jDistance(x,y,vehicles.v[i].x,vehicles.v[i].y)<=64) {
                        if(vehicles.v[i].driver==V_NO_PASS) {
                            v_id=vehicles.v[i].id;
                            drive=true;incar=true;
                        } else if(vehicles.v[i].free_seat()) {
                            vehicles.v[i].getin(id);
                            v_id=vehicles.v[i].id; incar=true;
                        }
                    }
                }
		    } else {
                if(npcs.n[n_id].action()) {n_id=-1;}
		    }

		}
	}
	if(act_bt[3]) {inv.show=!inv.show;}
    stime-=(stime>=0); rtime-=(rtime>=0);
}
void _p::draw() {
    if(editor.enabled) {editor.draw(id); return;}
	if(!incar) {
        if(nemesys()) {
            al_draw_scaled_rotated_bitmap(tex_zombie[1][int(ind)%8],64,64,x-view[id].x,y-view[id].y,0.35,0.35,DegToRad(-dir),0);
        } else {
            al_draw_scaled_rotated_bitmap(tex_player[0][int(ind)%8],32,32,x-view[id].x,y-view[id].y,0.35,0.35,DegToRad(-dir),0);
        }
	}
}
void _p::draw_gui() {
    if(editor.enabled) {return;}
    al_draw_textf(font,al_map_rgba(0,0,0,255),view[id].xport,view[id].yport,0,"%s %d/%d %s",wp[wp_pos].name,wp[wp_pos].ammopack,wp[wp_pos].ammo,(rtime>=0)?"reload":"");
    inv.draw(id);
    al_draw_filled_rectangle(view[id].xport,view[id].yport+view[id].hport*0.9,view[id].xport+view[id].wport*0.2*(hp/100.),view[id].yport+view[id].hport,al_map_rgb(255,0,0));
    al_draw_rectangle(view[id].xport,view[id].yport+view[id].hport*0.9,view[id].xport+view[id].wport*0.2,view[id].yport+view[id].hport,al_map_rgb(0,0,0),1);
}

void _players::set_contr(char id, char contr_type) {p[id].contr_type=contr_type;}
void _players::step() {for(int i=0;i<cnt;i++) {p[i].step();}}
void _players::draw(unsigned char id) {for(int i=0;i<cnt;i++) {p[i].draw();}}
void _players::draw_gui() {for(int i=0;i<cnt;i++) {p[i].draw_gui();}}
