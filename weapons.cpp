#include "weapons.h"
#include <cstdlib>
#include <cstdio>
using namespace std;
Weapon::Weapon(char* nameIn, int min, int max, int miss){
	this->name = nameIn;
	this->minDamage = min;
	this->maxDamage = max;
	this->missChance = miss; //IS ACTUALLY HIT CHANCE

}

int Weapon::calcDamage(){
	int damage = 0;
	if(rand() % 100 >  this->missChance){
		return 0;
	}
	damage = (rand() % (this->maxDamage - this->minDamage)) + this->minDamage;
	return damage;	
}
void Weapon::printWeaponStats(){
	printf("Name:%s\nMinimum Damage: %d\nMaximum Damage: %d\nHit Chance: %d%\n",
			this->name,
			this->minDamage,
			this->maxDamage,
			this->missChance);

}
