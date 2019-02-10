#ifndef LOCATIONS_HEADER
#define LOCATIONS_HEADER
class Location{
public:
	char* name;
	bool destroyed;
	Location(char * name){
		this->name = name;
		destroyed = false;		
	}
};
#endif
