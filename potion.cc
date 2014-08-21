#include "potion.h"
#include "player.h"
#include <iostream>
void Potion::effect(){}
void Potion::nullify(){}
void potHP::use(){
Floor * f = Floor::getInstance();
	Entity * empty = new Entity(getX(), getY());	//replace the potion's position in the map with an empty entity
	f->replace(empty, getX(), getY(), true);
	if(!getPositive() && !used) used=true;
	else if(!used){
		effect();	//only apply effect if its not used
		used = true;
	}
}
void Potion::use(){
	std::cout << "0";
	if(!used){ 
		std::cout << "FUCK ALL NIGGERS";
		effect();	//only apply effect if its not used
		Entity * empty = new Entity(getX(), getY());	//replace the potion's position in the map with an empty entity
		fl->replace(empty, getX(), getY(), true);	//must keep used potions pointer somewhere....CHAMBER
		used = true;
	}
}
void Potion::stopUse(){
	if(used) nullify();
}
void potAtk::effect(){
	p->usePotion(this);
	if(this->getPositive())
		p->newAction("PC uses BA");
	else
		p->newAction("PC uses WA");
}
void potAtk::nullify(){
	bool x = (getPositive()) ? false: true;
	setPositive(x);
	p->usePotion(this);
}

void potHP::effect(){
	if(getPositive())
	{
		p->usePotion(this);
		p->newAction("PC uses RH");
	}
	else if(turns <= 10)
	{
		p->usePotion(this);
		if(turns == 1)
			p->newAction("PC uses PH");
		++turns;
	}
}
void potHP::nullify(){}

void potDef::effect(){
	p->usePotion(this);
	if(this->getPositive())
		p->newAction("PC uses BD");
	else
		p->newAction("PC uses WD");
}
void potDef::nullify(){
	bool x = (getPositive()) ? false: true;
	setPositive(x);
	p->usePotion(this);
}