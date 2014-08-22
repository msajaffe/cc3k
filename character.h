#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <string>
#include "entity.h"
#include "floor.h"
class Character : public Entity{
int HP, Atk, Def;
std::string race;
Floor *fl;
protected:
	Entity * oldTile;
public:
	/*virtual*/ int add();	//adds character to floor
	void changeStats(int HP, int Atk, int Def); //inc/dec stats
	Character(int x, int y, char c, std::string type = "character"): Entity(x, y, c, type){	
		fl = getFloor();
		oldTile = NULL;
		HP = Atk = Def = 0;
		race = "";
	}
	int getAtk() { return Atk; }
	int getDef() { return Def; }
	int getHP() { return HP; }
	std::string getRace() {return race;}
	void changeRace(std::string s) {race=s;}
	Floor * getFloor(){ 
		fl = Floor::getInstance();
	    return fl; }
};

#endif
