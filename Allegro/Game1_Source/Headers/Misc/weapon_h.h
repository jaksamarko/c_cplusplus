#define WEAPON_KNIFE 0
#define WEAPON_GUN 1
#define WEAPON_MACHINEGUN 2
#define WEAPON_SHOTGUN 3

class weapon {
    unsigned char type;
    public:
    char name[25];
    short int ammo,ammopack,maxammo,maxammopack,shoot_time,reload_time,dmg;
    weapon() {ammo=ammopack=maxammo=shoot_time=maxammopack=reload_time=0;}
	void equip(unsigned char type);
};
