#include "player.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
Player::Player(){
	this->health = 100;
	this->shield = 100;	
	this->consumable;
	this->dead = false;
}
Player::~Player(){
	free(weapons);
	free(consumable);
}
void Player::takeDamage(int damage){
	if(shield > 0){
		shield -= damage;
		if(shield <= 0){
			health -= (-1) * shield;
			shield = 0;
		}

	}else{
	health -= damage;
	}
	if(health <= 0){
		this->die();
	}
	
}
int Player::takeConsume(){
	if(consumable != NULL){
		if(consumable->resource == 'h'){
			health += consumable->amount;
			if(health > 100){
				health = 100;
			}
		}
		if(consumable->resource == 's'){
			shield += consumable->amount;
			if(shield > 100){
				shield = 100;
			}
		}
		if(consumable->resource == 'b'){
			int difference = 0;
			health += consumable->amount;
			if(health > 100){
				difference = health - 100;
				health = 100;
			}
			shield += difference;
			if(shield > 100){
				shield = 100;
			}
		}
		if(consumable->resource == 'r'){
			health = 100;
			shield = 100;
			consumable = NULL;
			return 0;
		}
		cout << "You healed for " << consumable->amount << endl;
	}
	else{
		std::cout << "YOU CANT USE A F*CKIN CONSUMABLE IF YOU DONT HAVE A F*CKIN CONSUMABLE! YOU WASTED YOUR TURN!" << std::endl;
	}
	consumable = NULL;
	return 1;
	
}
void Player::die(){
	this->dead = true;
}
