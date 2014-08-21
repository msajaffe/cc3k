#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <vector>
#include "textdisplay.h"
#include "entity.h"

class Treasure;
class Chamber;
class Player;
class Floor {	//singleton pattern
int width, length;
TextDisplay * td;
Floor(int length, int width);
int currentFloor;
bool win;
static Floor *instance;
void fillChamber(Chamber * ch, Entity * tile);
public:
std::vector<Entity *> * ent;
Chamber ** ch;
	static Floor *getInstance(int length, int width);
	static Floor *getInstance();
	~Floor(){
		while(!ent->empty()) {
			delete ent->back(); 
			ent->pop_back();
			delete instance;
		}
		delete ent;
		delete td;
	}
	void notify(Entity *);
	int getWidth(){return width;}
	int getLength(){return width;}
	bool getWinState(){return win;}
	Entity * replace(Entity * e, int x, int y, bool newEnt = false, Entity * old = NULL);
	void draw(Player *p, bool won = false);
	bool validMove(int x, int y, bool player = false);
	void changeGold(int x);
	void initChambers();
	Player * exitLevel(Player * p, std::string race = "");
	int turn(Player * p);
	Player * generate(Player * p, std::string = "");
	
};


#endif
