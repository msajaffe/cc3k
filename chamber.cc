#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <math.h>
#include "floor.h"
#include "entity.h"
#include "character.h"
#include "item.h"
#include "potion.h"
#include "player.h"
#include "chamber.h"
#include "treasure.h"
#include "enemy.h"

using namespace std;


void Chamber::atExit(Floor * f){
	int pos = 0;
		while(!pots->empty()) {
			pots->back()->stopUse();
			if (!pots->back()->getUsed()){
				int x = pots->back()->getX(); int y = pots->back()->getY();
				Entity * empty = new Entity(x, y);	
				f->replace(empty, x, y, true);	
			}
			delete pots->back();
			pots->pop_back();
		}
	while(!tr->empty()) {
			int x = tr->back()->getX(); int y = tr->back()->getY();
			if (tr->back()->getValue() != -1) {
				Entity * empty = new Entity(x, y);	
				f->replace(empty, x, y, true);	
			} 
			delete tr->back();
			tr->pop_back();
		}
	while(!en->empty()) {
			int x = en->back()->getX(); int y = en->back()->getY();
			if(!en->back()->enemyDead()) {
				Entity * empty = new Entity(x, y);	
				f->replace(empty, x, y, true);
			} 
			delete en->back();			
			en->pop_back();
		}
		if(stairs){ 
			Entity * empty = new Entity(stairs->getX(), stairs->getY());	
			Entity * tmp = f->replace(empty, stairs->getX(), stairs->getY(), true);	
			stairs = 0;
		}
}
Chamber::~Chamber(){
	delete pots;
	delete myMap;
	delete en;
	delete tr;
}

void Chamber::potionTurn(Floor *f)
{
	for(int j=0; j<pots->size(); ++j)
	{
		if(pots->at(j)->getUsed() && pots->at(j)->getLongEffect())
		{
			if(static_cast<potHP *>(pots->at(j))->getTurns() != -1 && static_cast<potHP *>(pots->at(j))->getTurns() <= 10)
			{
				static_cast<potHP *>(pots->at(j))->effect();
			}
		}
	}
}

int Chamber::enemyTurn(Player * p){
	if(p->getActionMade())
	{
		for (int i = 0; i < en->size(); i++){ 
			if (en->at(i)->inOBR(p)){ 
				if (p->isDead()) return 1;
				en->at(i)->attack(p);
			} else if (en->at(i)->getMoveable()) en->at(i)->move();
		}
	}
	if (p->isDead()) return 1;
	return 0;
}
void Chamber::addPot(Potion * pot){
	pots->push_back(pot);
}
void Chamber::addEnemy(Enemy * enemy){
	en->push_back(enemy);
}
void Chamber::addTreasure(Treasure * tr){
	this->tr->push_back(tr);
}
void Chamber::addTile(int x, int y){
	myMap->push_back(make_pair(x,y));
}
bool Chamber::insideChamber(int x, int y){
	return (find(myMap->begin(), myMap->end(), make_pair(x, y)) != myMap->end());
	}