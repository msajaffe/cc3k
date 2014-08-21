#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>
#include <iostream>
#include "entity.h"
#include "floor.h"
class Character;
class Item: public Entity {
bool available; //always true for normal (loots), false until merchant/drag slain for others. false until close enough to use potion.
Floor * f;
public:
	Item(int x, int y, char c, std::string type): Entity(x, y, c, type), available(false){
		f = Floor::getInstance();
	}
	int add();
	
};

#endif

