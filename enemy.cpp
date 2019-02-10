#include "enemy.h"
#include <cstdlib>
#include <cstdio>
Enemy::Enemy(Player * p, Weapon * w){
	this->health = rand()%50 + 50;
	this->shield = rand()%100;
	this->player = p;
	this->weapon = w;
}

void Enemy::takeDamage(int damage){
	if(shield > 0){
		shield -= damage;
		if(shield <= 0){
			health -= (-1) * shield;
			shield = 0;
		}
	}
	else{
		health -= damage;
	}
	if(health <= 0){
		this->die();
	}

}
void Enemy::die(){
	//GIVE PLAYER OPTION TO PICK UP WEAPON
	//printf("Would you like to take the enemy's %s", this->weapon->name);	
	//USER INPUT PROMPT
	//IF YES THEN PROMPT WHICH INVENTORY ITEM TO SWITCH OUT
}
int Enemy::dealDamage(){
	int damage = weapon->calcDamage();
	player->takeDamage(damage);
	return damage;
}
