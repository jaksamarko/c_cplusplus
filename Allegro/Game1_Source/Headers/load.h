#define LANG_HUN 1
#define LANG_ENG 0

unsigned char lang=LANG_ENG;

void M_play() {menu.setpage(MENU_PLAY);}
void M_opt() {menu.setpage(MENU_OPTION);}
void M_cre() {menu.setpage(MENU_CREDIT);}
void M_exit() {game.close();menu.close();}
void M_start() {menu.close();game.open();}
void M_back() {menu.setpage(MENU_MAIN);}

void menu_setup() {
    game_mode_texts=new char**[2];
    players_texts=new char**[2];
    for(int j=0;j<2;j++) {
        game_mode_texts[j]=new char*[5];
        players_texts[j]=new char*[5];
        for(int k=0;k<5;k++) {game_mode_texts[j][k]=new char[15];players_texts[j][k]=new char[15];}
        switch(j) {
            case LANG_ENG:
                strcpy(game_mode_texts[j][0],"Campaign");
                strcpy(game_mode_texts[j][1],"Survival");
                strcpy(game_mode_texts[j][2],"Versus mode");
                strcpy(game_mode_texts[j][3],"Waves");
                strcpy(game_mode_texts[j][4],"Nemesys");

                strcpy(players_texts[j][0],"1 player");
                strcpy(players_texts[j][1],"2 player");
                strcpy(players_texts[j][2],"3 player");
                strcpy(players_texts[j][3],"4 player");
            break;
            case LANG_HUN:
                strcpy(game_mode_texts[j][0],"Kampany");
                strcpy(game_mode_texts[j][1],"Tulelo");
                strcpy(game_mode_texts[j][2],"Versus mod");
                strcpy(game_mode_texts[j][3],"Hullam");
                strcpy(game_mode_texts[j][4],"Nemesis");

                strcpy(players_texts[j][0],"1 jatekos");
                strcpy(players_texts[j][1],"2 jatekos");
                strcpy(players_texts[j][2],"3 jatekos");
                strcpy(players_texts[j][3],"4 jatekos");
            break;
        }
    }

	menu.setsize(800,450);
	menu.setfont(font,al_map_rgb(255,255,255),al_map_rgb(255,0,0));
	menu.add(MENU_MAIN,menu.w*0.05,menu.h*0.2,menu_texts[0][lang],&M_play);
	menu.add(MENU_MAIN,menu.w*0.05,menu.h*0.4,menu_texts[1][lang],&M_opt);
	menu.add(MENU_MAIN,menu.w*0.05,menu.h*0.6,menu_texts[4][lang],&M_cre);
	menu.add(MENU_MAIN,menu.w*0.05,menu.h*0.8,menu_texts[2][lang],&M_exit);

	menu.add(MENU_PLAY,menu.w*0.45,menu.h*0.5,game_mode_texts[lang],5);
	menu.add(MENU_PLAY,menu.w*0.45,menu.h*0.6,players_texts[lang],4);
	menu.add(MENU_PLAY,menu.w*0.05,menu.h*0.7,menu_texts[6][lang],&M_start);
	menu.add(MENU_PLAY,menu.w*0.05,menu.h*0.8,menu_texts[3][lang],&M_back);

	menu.add(MENU_OPTION,menu.w*0.05,menu.h*0.8,menu_texts[3][lang],&M_back);

	menu.add(MENU_CREDIT,menu.w*0.05,menu.h*0.8,menu_texts[3][lang],&M_back);
}

void npc_1(npc *n) {
    switch(gm.quest) {
        case 0:
            switch(n->tind) {
                case 0:
                    tBox.spawn("Hi, this is a test textbox! Enjoy it! ;)");
                break;
                case 1:
                    tBox.spawn("Another textbox test, bitches");
                break;
                default: gm.quest++; n->tind=-1; break;
            }
        break;
        case 2:
            switch(n->tind) {
                case 0: gm.quest++; tBox.spawn("Now your second quest is done!"); break;
                default: n->tind=-1; break;
            }
        break;
        default:
            switch(n->tind) {
                case 0: tBox.spawn("Im just an npc!"); break;
                default: n->tind=-1; break;
            }
        break;
    }
}

void npc_2(npc *n) {
    switch(gm.quest) {
        case 0:
            switch(n->tind) {
                case 0: tBox.spawn("You should check out the other npc!"); break;
                default: n->tind=-1; break;
            }
        break;
        case 1:
            switch(n->tind) {
                case 0: tBox.spawn("Hi this is your second quest, to talk me!"); break;
                case 1: gm.quest++; tBox.spawn("Aaand its done!"); break;
                default: n->tind=-1; break;
            }
        break;
        case 2:
            switch(n->tind) {
                case 0: tBox.spawn("Now go and talk with the first npc!"); break;
                default: n->tind=-1; break;
            }
        break;
        default:
            switch(n->tind) {
                case 0: tBox.spawn("Im just here for no reason!"); break;
                default: n->tind=-1; break;
            }
        break;
    }
}

void npc_setup() {
    npcs.create(0,150,0,"Test NPC",&npc_1);
    npcs.create(100,0,0,"Test NPC2",&npc_2);
}

void cutscene_setup() {
    cutscenes.add(0,"Hi, challanger!");
    cutscenes.add(0,"This is my first cutscene!Is it good??");
}


void init() {
    jSetAA(true);
    for(int i=0;i<1;i++) {tex_player[i]=jLoadAnim("Files/player.png",8);}
    tex_zombie[0]=jLoadAnim("Files/zombie_stand.png",1);
    tex_zombie[1]=jLoadAnim("Files/zombie_move.png",8);
    tex_zombie[2]=jLoadAnim("Files/zombie_die.png",5);
    tex_zombie[3]=jLoadAnim("Files/zombie_headshot.png",8);
    tex_zombie[4]=jLoadAnim("Files/zombie_hurt.png",5);
    tex_zombie[5]=jLoadAnim("Files/zombie_attack.png",6);
    tex_gui=jLoadAnim("Files/gui.png",1);
    tex_blood=jLoadAnim("Files/blood.png",2);
    tex_powups=jLoadAnim("Files/powup.png",2);
    tex_grass=al_load_bitmap("Files/grass.png");
    font=al_load_ttf_font("Files/font.ttf",24,0);
    tex_item=jLoadAnim("Files/item.png",1);
    tex_buildings=jLoadAnim("Files/obj.png",BUILDINGS_COUNT);
    tex_vehicles=jLoadAnim("Files/vehicle.png",VEHICLES_COUNT);

    menu_setup();
    npc_setup();
    cutscene_setup();
    world.load();
}

void save() {
    world.save();
}
