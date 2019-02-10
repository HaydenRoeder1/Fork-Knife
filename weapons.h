#ifndef WEAPON_HEADER
#define WEAPON_HEADER
#include <string>
#include <cstdlib>
using namespace std;
class Weapon{
public:
	char* name;
	int minDamage;
	int maxDamage;
	int missChance; //0-100

	Weapon(char*, int,int,int);
	~Weapon(){
		free(name);
	}	
	int calcDamage();
	void printWeaponStats();
};
#endif
