#include "entity.h"
#include "floor.h"
int Entity::add(){ 
Floor * fl = Floor::getInstance();
	if(fl->validMove(getX(), getY())){
		Entity * tmp = fl->replace(this, getX(), getY(), true);
		delete tmp;
		return 0;
	}
	return 1;
}
int Entity::getX(){ return x; }
int Entity::getY(){ return y; }
char Entity::getChar(){ return c; }
std::string Entity::getType(){ return type; }
void Entity::setStats(int x, int y, char ch, std::string type){
	this->x = x;
	this->y = y;
	c = ch;
	this->type = type;
}