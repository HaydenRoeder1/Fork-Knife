#ifndef ENEMY_HEADER
#define ENEMY_HEADER
#include "player.h"
#include "weapons.h"
class Enemy{
public:
	int health;
	int shield;
	Weapon * weapon;
	Player * player;
	Enemy(Player*, Weapon*);
	void takeDamage(int);
	int dealDamage();
	void die();



};
#endif
