#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include "weapons.h"
#include "consumable.h"
using namespace std;
class Player{
public:
	int health;
	int shield;
	bool dead;
	Weapon * weapons[4];
	Consumable * consumable;
	Player();
	~Player();
	void takeDamage(int damage);
	void dealDamage();//REQUIRES A POINTER TO ENEMY
	int takeConsume();
	void die();
};
#endif
