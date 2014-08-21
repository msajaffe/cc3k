#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <string>
#include "textdisplay.h"
class Floor;
class Entity {	
int x, y;
char c;
std::string type;
int colour;
public:
	Entity(int x, int y, char c = '.', std::string type = "empty"): x(x), y(y), c(c), type(type){}
	int getX(); //returns the x coordinate of the entity;
	int getY(); //returns the y coordinate of the entity
	virtual int add();
	char getChar();
	int getColour(){ return colour; }
	std::string getType();
	void setStats(int x, int y, char ch, std::string type);
	//bool inRadius();		
};

#endif