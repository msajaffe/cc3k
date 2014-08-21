#ifndef __CHAMBER_H__
#define __CHAMBER_H__
#include <vector>
#include <map>
#include "entity.h"
class Potion;
class Floor;
class Enemy;
class Treasure;
class Chamber{
std::vector<std::pair<int,int> > * myMap;
std::vector<Potion *> * pots;
std::vector<Enemy *> * en;
std::vector<Treasure *> *tr;
Entity * stairs;
int length, width;
bool inthis;
public: 
	Chamber(): pots(new std::vector<Potion *>), en(new std::vector<Enemy *>), tr(new std::vector<Treasure *>), length(0), width(0), inthis(false){
		myMap = new std::vector<std::pair<int,int> >;
	}
	void addPot(Potion *);
	void addEnemy(Enemy *);
	void addTreasure(Treasure *);
	int enemyTurn(Player * p);
	void potionTurn(Floor *f);
	void addTile(int x, int y);
	bool insideChamber(int x, int y);
	void atExit(Floor *);
	void deleteEnemy(int x, int y, Floor*fl){ 
		int pos = y*fl->getWidth() + x-1;
		en->erase(en->begin() + (pos));
	}
	void setStairs(Entity * s){
		stairs = s;
	}
	
	std::vector<std::pair<int,int> > * getMap(){ return myMap; }
	~Chamber();
};

#endif
