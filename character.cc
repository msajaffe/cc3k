#include "character.h"
#include "floor.h"
#include <iostream>
void Character::changeStats(int HP, int Atk, int Def){
	this->HP += HP;
	this->Atk += Atk;
	this->Def += Def;
} 

int Character::add(){
fl = getFloor();
	if(fl->validMove(getX(), getY())){
		Entity * tmp = fl->replace(this, getX(), getY(), true);
		delete tmp;
		return 0;
	}
	return 1;
}	
