#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "character.h"
#include <string>
#include <cstdlib>
class Player;
class Treasure;
class Enemy : public Character
{
	Floor *f;
	protected:
		bool hostility, moveable;
		int dropAmount;
	public:
		Enemy(int x, int y, char c, std::string type = "character"): Character(x,y,c,type) 
		{
			f = Floor::getInstance();
		}
		void move();
		void attack(Player *p);
		bool getMoveable(){ return moveable; }
		virtual bool enemyDead();
		void toggleMoveable() {moveable = (moveable) ? false : true;}
		bool inOBR(Entity *target, Entity *e = 0);
		int getDropAmount(){return dropAmount;}
		void setHostility(bool h){ hostility = h; }
		virtual bool checkHostility(Player * p = 0){ return hostility; }
};

class Vampire : public Enemy
{
	Floor *f;
	public:
		Vampire(int x, int y, char c = 'V', std::string type ="character") : Enemy(x, y, c, type)
		{
			hostility = true;
			moveable = true;
			dropAmount = 1;
			changeStats(50,25,25);
			f = Floor::getInstance();
			changeRace("Vampire");
		}
};

class Werewolf : public Enemy 
{
	Floor *f;
	public:
		Werewolf(int x, int y, char c = 'W', std::string type ="character") : Enemy(x, y, c, type)	
		{
			hostility = true;
			moveable = true;
			dropAmount = 1;
			changeStats(120,30,5);
			f = Floor::getInstance();
			changeRace("Werewolf");
		}
};

class Goblin : public Enemy
{
	Floor *f;
	public:
		Goblin(int x, int y, char c = 'N', std::string type ="character") : Enemy(x, y, c, type)
		{
			hostility = true;
			moveable = true;
			dropAmount = 1;
			changeStats(70,5,10);
			f = Floor::getInstance();
			changeRace("Goblin");
		}
};

class Troll : public Enemy
{
	Floor *f;
	public:
		Troll(int x, int y, char c = 'T', std::string type ="character") : Enemy(x, y, c, type)
		{
			hostility = true;
			moveable = true;
			dropAmount = 1;
			changeStats(120,25,15);
			f = Floor::getInstance();
			changeRace("Troll");
		}
};

class Phoenix : public Enemy
{
	Floor *f;
	public:
		Phoenix(int x, int y, char c = 'X', std::string type ="character") : Enemy(x, y, c, type)
		{
			hostility = true;
			moveable = true;
			dropAmount = 1;
			changeStats(50,35,20);
			f = Floor::getInstance();
			changeRace("Phoenix");
		}
};

class Merchant : public Enemy
{
	Floor *f;
	public:
		Merchant(int x, int y, char c = 'M', std::string type ="character") : Enemy(x, y, c, type)
		{
			hostility = false;
			moveable = true;
			dropAmount = 4;
			changeStats(30,70,5);
			f = Floor::getInstance();
			changeRace("Merchant");
		}
		bool checkHostility(Player *p);
};


class Dragon : public Enemy
{
	Floor *f;
	Treasure *dHoard;
	public:
		Dragon(int x, int y, Treasure *d, char c = 'D', std::string type = "character") : dHoard(d), Enemy(x, y, c, type)
		{
			hostility = false;
			moveable = false;
			dropAmount = 6;
			changeStats(150,20,20);
			f = Floor::getInstance();
			changeRace("Dragon");
		}
		bool checkHostility(Player *p);
		bool enemyDead();
		~Dragon(){
			dHoard = NULL;
		}
};

#endif