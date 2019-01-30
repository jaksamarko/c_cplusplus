void weapon::equip(unsigned char type) {
    this->type=type;
    switch(type) {
        case WEAPON_KNIFE: ammo=0; ammopack=0; shoot_time=0; reload_time=globalfps; dmg=50; strcpy(name,"KNIFE"); break;
        case WEAPON_GUN: ammo=30; ammopack=90; shoot_time=7; reload_time=globalfps; dmg=50; strcpy(name,"GUN"); break;
        case WEAPON_MACHINEGUN: ammo=100; ammopack=200; shoot_time=3; reload_time=60; dmg=50; strcpy(name,"MACHINEGUN"); break;
        case WEAPON_SHOTGUN: ammo=12; ammopack=36; shoot_time=50; reload_time=60; dmg=50; strcpy(name,"SHOTGUN"); break;
    }
    maxammo=ammo;
    maxammopack=ammopack;
}
