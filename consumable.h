#ifndef CONSUMABLE_HEADER
#define CONSUMABLE_HEADER
#include <cstdlib>
class Consumable{
public:
	char* name;
	int amount;
	char resource;
	~Consumable(){
		free(name);
	}
	Consumable(char*,int, char);
};
#endif
