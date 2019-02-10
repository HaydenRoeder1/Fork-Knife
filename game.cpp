#include "weapons.h"
#include "player.h"
#include "consumable.h"
#include "enemy.h"
#include "locations.h"
#include "introtext.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

const int  NUM_WEAPONS = 24;
using namespace std;

int fight(Enemy * e, Player * p);
void printLocations(Location **);
void printInventory(Player * p, bool justWeap);
void generateLoot(Player * p, Weapon * w[], Consumable * c[] );
int prompt(int,int,char*);
int main(){
	srand(time(NULL));
	system("clear");
	int choice = -1;
	char line[5000];
	FILE * weaponsFile = fopen("weapons.txt", "r");
	FILE * consumeFile = fopen("consumables.txt", "r");
	FILE * locationFile = fopen("locations.txt", "r");
	FILE * introFile = fopen("intro.txt", "r");
	FILE * instructions = fopen("consumableInfo.txt", "r");
	Weapon * weapons[24];
	Consumable * consumables[7];
	Location * locations[21];

	Location * curLocation;
	int counter = 0;
	

	//READS IN ALL THE WEAPONS
	while(fgets(line, 300, weaponsFile)){
		char* tempName = (char*)malloc(sizeof(char) * 2000);
		int* tempMin = (int*)malloc(sizeof(int));
		int* tempMax = (int*)malloc(sizeof(int));
		int* tempMiss = (int*)malloc(sizeof(int));
		
		char*tempName2 = (char*)malloc(sizeof(char) * 2000);
		
		sscanf(line, "%[^,],%d,%d,%d", tempName, tempMin, tempMax, tempMiss);
			
		weapons[counter] = new Weapon(strcpy(tempName2, tempName), *tempMin, *tempMax, *tempMiss);
		counter++;
		
		free(tempName);
		free(tempMin);
		free(tempMax);
		free(tempMiss);
	}
	
	//READS IN ALL THE CONSUMABLES
	counter = 0;
	while(fgets(line, 300, consumeFile)){
		char* tempName = (char*)malloc(sizeof(char) * 2000); 
		int* tempAmt = (int*)malloc(sizeof(int));
		char* tempChar = (char*)malloc(sizeof(char));

		char* tempName2 = (char*)malloc(sizeof(char) * 2000);

		sscanf(line, "%[^,],%d,%c", tempName, tempAmt, tempChar);
		
		consumables[counter] = new Consumable(strcpy(tempName2, tempName), *tempAmt, *tempChar);
		counter++;
		free(tempName);
		free(tempAmt);
		free(tempChar);
	}
	//READS IN ALL LOCATIONS
	counter = 0;
	while(fgets(line, 300, locationFile)){
		char*tempName = (char*)malloc(sizeof(char) * 2000);
		locations[counter] = new Location(strcpy(tempName, line));
		counter++;
	}
	cout << "WARNING!!! THIS GAME CONTAINS SOME VERY STRONG LANGUAGE" << endl;
	choice = prompt(1,1, "Press 1 to continue...");
	//PRINTS INTRO STORY
	while(fgets(line, 200000000, introFile)){
		cout <<line;
	}
 		

	choice = prompt(1,1,"Press 1 To Continue...");
	cout << "Here's a list of weapons in the game, get them into that tiny brain of yours because you won't see these stats again" << endl;
	prompt(1,1,"Press 1 To Continue...");
	for(int i = 0; i < 24; i++){
		weapons[i]->printWeaponStats();
		cout<<endl;
	}
	prompt(1,1,"Got it? Press 1 to continue learning about the consumables in the game");
	while(fgets(line, 200000000, instructions)){
		cout<<line;
	}
	prompt(1,1,"Ok, thats everything you need to know, press 1 to drop in an duke it out with all the other chefs!");


	Player * p = new Player();
	int playerRemaining = 100;	
	int kills = 0;
	int turnSinceDestroy = 0;
	int townsDestroyed = 0;
	//START GAME
	printLocations(locations);
	choice = prompt(1,21,"Where ya droppin ya fat useless sack of yankee doodle dandy sh*t?");
	curLocation = locations[choice-1];

	p->weapons[0] = new Weapon("Fork", 15, 20, 100);
	p->consumable = consumables[0];



	cout << "Ya landed in the sh*thole of the world, " << curLocation->name << "Check out that fridge and see if you find anything" << endl;
	prompt(1,1, "Press 1 to open fridge");
	generateLoot(p, weapons, consumables);
	//MAIN GAME LOOP
	while(p->dead == false){
		if(playerRemaining > 25){
			playerRemaining -= rand() % 20;
		}else if(playerRemaining > 10){
			playerRemaining -= (rand() % 5) + 2;
		}else if(playerRemaining > 3){
			playerRemaining -= (rand() % 2) + 1;
		}
		printLocations(locations);
		choice = prompt(1,21,"Where the f*ck are you going?");
		curLocation = locations[choice - 1]; 
		if(curLocation->destroyed == true){
			cout << "YOU CAME TO THE WRONG TOWN! NOW FEEL MY WRATH YOU F*CKIN DEGENERATE!" << endl;
			break;
		}
		int option = rand() % 3;

		if(option == 0){
			cout << "Oh look, its a fridge in the middle of nowhere, go see what f*ckin mystery is in there" << endl;
			generateLoot(p, weapons, consumables);
		}else if(option == 1){
			cout << "Ya see that sorry *ss excuse for a chef over there? GO SHOW THEM WHAT A REAL CHEF LOOKS LIKE!" << endl;
			Enemy * enemy = new Enemy(p, weapons[rand() % 24]);
			int won = fight(enemy, p);
			if(won == 0){
				cout << "YOU SERIOUSLY F*CKIN CAME INTO MY COMPETETION AND DIED TO THAT WASTE OF SPACE?" << endl;
				break;
			}
			if(won == 1){
				playerRemaining -= 1;
				kills++;
			}
			if(won == 2){
				int newLocIndex = rand() % 21;
				cout << "There you go, you drank your f*ckin problems away. Now you woke up in " << locations[newLocIndex]->name  << endl;
				curLocation = locations[newLocIndex];
				if(curLocation->destroyed == true){
					cout << "AND THAT WAS A F*CKIN MISTAKE!" << endl;
					break;
				}
				prompt(1,1,"Press 1 to continue");
			}
		}else if(option == 2){
			int randResponse = rand() % 3;

			if(randResponse == 0){
				cout << "MOVE FASTER YOU PIG!" << endl;
			}
			else if(randResponse == 1){
				cout << "GET A MOVE ON!" << endl;
			}else{
				cout << "YOU MOVE LIKE OLD PEOPLE F*CK!" << endl;
			}
			
			choice = prompt(1,2, "1.YES SIR!\n2.Confront him");
			if(choice == 2){
				cout << "WHO THE F*CK ARE YOU TO BE TALKING BACK TO ME? IM F*CKING GORDON RAMSAY!" << endl;
				break;
			}
		}
		if(playerRemaining <= 1){
			cout << "As the last chef standing with " << kills << " kills, you're definitely gonna be my next top chef! VICTORY ROYALE!!!" << endl;
			return 0;
		}
		turnSinceDestroy++;
		system("clear");
		if(turnSinceDestroy > 5 && townsDestroyed < 18){
			turnSinceDestroy = 0;

			for(int i = 0; i < 3; i++){
				int randNum = rand() % 21;
				if(locations[randNum]-> destroyed == false){
					cout << "Gordon destroyed " << locations[randNum]->name << "." << endl;
					locations[randNum]->destroyed = true;
					townsDestroyed++;
				}
			}
		}
		cout << "Players Remaining: " << playerRemaining << endl;

		


	}



	//DEAD
	cout << "*Everything goes black* Two pieces of bread cover your ears, you hear an angry voice yelling 'YA F*CKIN DEAD YA IDIOT SANDWICH'" <<endl;

	return 0;




 



	delete p;
	fclose(weaponsFile);
	fclose(consumeFile);
	fclose(introFile);
	fclose(locationFile);
}









int fight(Enemy * e, Player * p){
	int choice;
	int damage;
	cout << "Looks like he's got a " << e->weapon->name << ", with " << e->health << " health and " << e->shield << " shield, shouldn't be much trouble" << endl;
	while(e->health > 0 && p->health > 0){
		damage = 0;
		printInventory(p, false);
		cout << "You're sittin pretty with " << p->health << " health" << " and " << p->shield << " shield" << endl;
		choice = prompt(0,4, "Ya gonna stand there or ya gonna hit him with something?");
		if(choice == 4){
			if(p->takeConsume() == 0){
				delete e;
				return 2;
			}
		}else{
			if(p->weapons[choice] != NULL){
				damage = p->weapons[choice]->calcDamage();
				if(damage == 0){
					cout << "You missed him. F*ckin brillient" << endl;
				}
				cout << "You " << p->weapons[choice]->name << "'d him for " << damage << " damage. Way to f*ckin go." << endl;
				e->takeDamage(damage);
			}
			else{
				cout << "What are you gonna do, tickle him? YOU WASTED YOUR TURN!" << endl;
			}
		}
		if(e->health <= 0){
			cout << "You killed him! That's what I like to see out of my chefs! Looks like he dropped his " << e->weapon->name << endl;
			choice = prompt(1,2, "You gonna pick it up or just stand there\n1. Pick up\n2. Stand There");
			if(choice == 1){
				printInventory(p, true);
				choice = prompt(0,3, "What are you dropping for it?");
				p->weapons[choice] = e->weapon;
				cout << "Alright then, keep moving" << endl;
				choice = prompt(1,1, "Press 1 to continue");
			}
			if(choice == 2){
				choice = prompt(1,1, "Get moving before I kick your worthless *ss\n 1.Scurry Away");
			}
			delete e;
			return 1;
		}
		cout << "He " << e->weapon->name << "'d you for " << e->dealDamage() << " damage. Get up you pansy" << endl;
		if(p->health <= 0){
			delete e;
			return 0;	
			
		}	
	}
	return 0;
}
void printLocations(Location ** locations){
	for(int i = 1; i <= 21; i++){
		if(locations[i-1]->destroyed == true){
		cout << i << ": " << locations[i-1]->name << "(Obliterated in Gordon's fit of rage)" << endl;
		}else{
			cout << i << ": " << locations[i-1]->name << endl;
		}
	}

}
void printInventory(Player * p, bool justWeap){
	printf("\n");
	printf("Inventory:\n");
	for(int i = 0; i < 4; i++){
		if(p->weapons[i] == NULL){
			printf("%d: Empty\n",i);
		}else{
			printf("%d: %s\n",i, p->weapons[i]->name);
		}
	}
	if(justWeap == false){
		if(p->consumable == NULL){
			printf("4: Empty\n");
		}else{
			printf("4: %s\n", p->consumable->name);
		}
	}
}
int prompt(int min, int max, char* text){
	printf("\n");
	int c = -20000;
	cout << text << endl;
	while(min > c || c > max){
		cin >> c;
	}
	return c;

}
void generateLoot(Player * p, Weapon * w[], Consumable * c[]){
	printf("\n");
	int choice;
	int consumeInd = 0;
	bool proccedConsume = false;
	if(rand() % 100 < 35 ){
		consumeInd = rand() % 7;
		proccedConsume = true;
	}
	int weaponInd = rand() % 24;

	if(proccedConsume){
		cout << "Congrats you f*ckin pig, you found a " <<c[consumeInd]->name << endl;
		choice = prompt(1,2,"Ya just gonna leave it there or ya gonna f*ckin pick it up?\n 1.Pick up\n 2.Leave it");
		if(choice == 1){
			if(p->consumable == NULL){
				p->consumable = c[consumeInd];
			}else{
				cout << "Well are you gonna trade that f*ckin " << p->consumable->name << " for it?" << endl;
				choice = prompt(1,2,"1. Yes Ramsay SIR!\n2. No");
				if(choice == 1){
					p->consumable = c[consumeInd];
					cout << "Alright pick it up and get moving!" << endl;
				}else{
					cout << "Quit wasting my time then! Get moving!" << endl;
				}
			}
			choice = prompt(1,1, "Press 1 to continue");

				
			
		}
	}else{
		cout << "What the hell is this " << w[weaponInd]->name << " doing in the fridge?" << endl;
		choice = prompt(1,2,"Ya want to take it?\n1. Yes\n2. No\n");
		if(choice == 1){
			printInventory(p, true);
			choice = prompt(0,3, "Where do you plan on putting it?");
			p->weapons[choice] = w[weaponInd];
		}
		cout <<  "Alright then keep moving you lazy pile of trash" << endl;
		choice = prompt(1,1, "Press 1 to continue");
		
	}
}
