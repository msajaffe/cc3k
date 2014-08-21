#ifndef __POTION_H__
#define __POTION_H__
#include "item.h"
class Player;
class Human;
class Potion: public Item {
bool available, positive;
Floor * fl;
protected:
	std::string potName;
	bool longEffect, used;
    virtual void effect();
	virtual void nullify();
	void setPositive(bool x){positive = x;}
public:
	Potion(int x, int y, char c = 'P', std::string type = "item", bool available = false, bool pos = true): Item(x, y, c, type), available(available), positive(pos){
		fl = Floor::getInstance();
		used = false;
		longEffect = false;
		potName = "";
	}
	virtual void use(); //effect instance gets decorated, Player gets notified
	void stopUse(); //get notified by Player that pot is no longer in use
		// does nothing if permanent use*/
	bool getPositive(){ return positive; }
	bool getUsed(){ return used; }
	bool getLongEffect(){return longEffect;}
	std::string getPotName(){return potName;}
};
class potAtk: public Potion {
Player * p;
public:
	potAtk(Player * h, bool pos, int x, int y, char c = 'P', std::string type = "item", bool available= false): Potion(x, y, c, type, available, pos){
		p = h;
		potName = pos ? "BA" : "WA";
	}
	void effect();
	void nullify();
};
class potHP: public Potion {
Player * p;
int turns;
public:
	potHP(Player * h, bool pos, int x, int y, char c = 'P', std::string type = "item", bool available= false): Potion(x, y, c, type, available, pos){
		p = h;
		longEffect = getPositive() ? false : true;
		if(this->getPositive())
			turns = -1;
		else
			turns = 1;
		potName = pos ? "RH" : "PH";
	}
	void effect();
	void nullify();
	void use();
	int getTurns(){return turns;}
};
class potDef: public Potion {
Player * p;
public:
	potDef(Player * h, bool pos, int x, int y, char c = 'P', std::string type = "item", bool available= false): Potion(x, y, c, type, available, pos){
		p = h;
		potName = pos ? "BD" : "WD";
	}
	void effect();
	void nullify();
};

#endif