#include "treasure.h"
#include "player.h"
#include <iostream>
void Treasure::effect(){	//add gold
	//ALREADY CHECKED IF VALID MOVE
	if(available)
	{
		p->pickUpGold(value);
		Entity * empty = new Entity(getX(), getY());	
		Entity * old = fl->replace(empty, getX(), getY(), true);
		available = false;
		value = -1;
	}
}
void Treasure::setAvailability(bool b) { available = b;}
bool Treasure::getAvailable(){ return available; }