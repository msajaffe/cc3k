#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "character.h"
#include <vector>
class Potion;
class potAtk;
class potDef;
class potHP;
class Enemy;

class Player: public Character{
Floor *fl;
bool attackedMerchant, actionMade;
std::string action;
double score;
protected:
	bool seenBefore[6]; //0 RH
	                    //1 BA
	                	//2 BD
	                	//3 PH
	                	//4 WA
	               		//5 WD
	int gold;
	int bHP;
	int bAtk;
	int bDef;
public:
	Player(int x, int y, char c = '@', std::string type = "character"): Character(x,y,c,type) {
		fl = Floor::getInstance();
		gold = 0;
		attackedMerchant=false;
		action = "Player character has spawned";
		for(int i=0; i<6; ++i)
			seenBefore[i] = false;
	}
	void move(std::string move);
	void usePotion(Potion * pot);
	bool getAttackedMerchant();
	void attack(Enemy *e, std::string move);
	void modifyAction(std::string s) {action += s;}
	void newAction(std::string s) {action = s;}
	bool isDead();
	int getScore() 
	{
		score = gold;
		score = getRace()=="Human" ? score*1.5 : score;
		return (int)score;
	}
	int getGoldAmount(){return gold;}
	std::string getAction(){return action;}
	int getBaseHP(){return bHP;}
	int getBaseAtk(){return bAtk;}
	int getBaseDef(){return bDef;}
	bool getSeenBeforeAt(int i){return (i>=0 && i<=5) ? seenBefore[i] : false;}
	void setActionMade(bool b){actionMade = b;}
	bool getActionMade(){return actionMade;}
	virtual void usePotion(potAtk *);
	virtual void usePotion(potDef *);
	virtual void usePotion(potHP *);
	virtual void pickUpGold(int value);
	void setGold(int x) { gold = x; }
};

class Human: public Player {
Floor *fl; 
public:
	Human(int x, int y, char c = '@', std::string type = "character"): Player(x,y,c,type) {
		fl = getFloor();
		changeRace("Human");
		bHP = 140;
		bAtk = 20;
		bDef = 20;
		changeStats(bHP, bAtk, bDef);
	}
};
class Dwarf: public Player {
Floor *fl; 
public:
	Dwarf(int x, int y, char c = '@', std::string type = "character"): Player(x,y,c,type) {
		fl = getFloor();
		changeRace("Dwarf");
		bHP = 100;
		bAtk = 20;
		bDef = 30;
		changeStats(bHP, bAtk, bDef);
	}
	void pickUpGold(int value);
};
class Elf: public Player {
Floor *fl; 
public:
	Elf(int x, int y, char c = '@', std::string type = "character"): Player(x,y,c,type) {
		fl = getFloor();
		changeRace("Elf");
		bHP = 140;
		bAtk = 30;
		bDef = 10;
		changeStats(bHP, bAtk, bDef);
	}
	void usePotion(potAtk *);
	void usePotion(potDef *);
	void usePotion(potHP *);
};

class Orc: public Player {
Floor *fl; 
public:
	Orc(int x, int y, char c = '@', std::string type = "character"): Player(x,y,c,type) {
		fl = getFloor();
		changeRace("Orc");
		bHP = 180;
		bAtk = 30;
		bDef = 25;
		changeStats(bHP, bAtk, bDef);
	}
	void pickUpGold(int value);
};
#endif