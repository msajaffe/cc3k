#ifndef __TREASURE_H__
#define __TREASURE_H__
#include "item.h"
class Player;
class Treasure: public Item {
Player * p;
bool available;
Floor * fl;
int value;
public:
	Treasure(Player *h, int x, int y, int value=1, bool avail = true, char c = 'G', std::string type = "item"): p(h), value(value), Item(x, y, c, type), available(avail){
		fl = Floor::getInstance();
		if (value == 6) available = false;
	}
	void effect();	//add gold
		//merchant/drag hoard should be observers of merchant/drag
	int getValue() { return value; }
	bool getAvailable();
	void setAvailability(bool b);
};

#endif