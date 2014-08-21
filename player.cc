#include "player.h"
#include "potion.h"
#include "treasure.h"
#include "chamber.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "enemy.h"
#include <sstream>

void Player::usePotion(Potion * pot){}
void Player::usePotion(potAtk * pot){	//VISITOR METHOD USED...CALLED FROM POTION
	int val = (pot->getPositive()) ? 5: -5;	//effect on attack is negative or positve depending on the potion typ
	if(this->getAtk() + val < 0)	//cant go less than 0
		changeStats(0, this->getBaseAtk() - this->getAtk(), 0);
	else	
		changeStats(0,val,0);	//if not less than 0 then change by desired stats
	int i = pot->getPositive() ? 1 : 4;
	seenBefore[i] = true;
}
void Player::usePotion(potDef * pot){	//SAME IDEA
	int val = (pot->getPositive()) ? 5: -5;
	if(this->getDef() + val < 0)
		changeStats(0, 0, this->getBaseDef() - this->getDef());
	else
		changeStats(0,0,val);
	int i = pot->getPositive() ? 2 : 5;
	seenBefore[i] = true;
}
void Player::usePotion(potHP * pot){	//SAME IDEA
	int val = (pot->getPositive()) ? 10: -1;
	if(getHP()+val <= getBaseHP())
		changeStats(val,0,0);
	else
		changeStats(getBaseHP()-getHP(), 0, 0);
	int i = pot->getPositive() ? 0 : 3;
	seenBefore[i] = true;
}
bool Player::isDead()
{
	return (this->getHP() <= 0);
}
void Player::pickUpGold(int value){
	gold += value;
}
bool Player::getAttackedMerchant() {return attackedMerchant;}

void Player::attack(Enemy *e, std::string move)
{//LOOOK INTO DESIRED DIRECTION OF ATTACK
	if(move == "no")
	{
		if(!(e->getY() == this->getY()-1 && e->getX() == this->getX()))	//IF THERE IS NO ENEMY THERE THEN EXIT FUNCTION
			return;
	}
	else if(move == "so")
	{
		if(!(e->getY() == this->getY()+1 && e->getX() == this->getX()))
			return;
	}
	else if(move == "ea")
	{
		if(!(e->getX() == this->getX()-1 && e->getY() == this->getY()))
			return;
	}
	else if(move == "we")
	{
		if(!(e->getX() == this->getX()+1 && e->getY() == this->getY()))
			return;
	}
	else if(move == "ne")
	{
		if(!(e->getX() == this->getX()-1 && e->getY() == this->getY()-1))
			return;
	}
	else if(move == "se")
	{
		if(!(e->getX() == this->getX()-1 && e->getY() == this->getY()+1))
			return;
	}
	else if(move == "sw")
	{
		if(!(e->getX() == this->getX()+1 && e->getY() == this->getY()+1))
			return;
	}
	else if(move == "nw")
	{
		if(!(e->getX() == this->getX()+1 && e->getY() == this->getY()-1))
			return;
	}

	if(e->getChar() == 'M')	//IF ATTACKING MERCHANT THEN LET EM KNOW
		this->attackedMerchant = true;

	int damage = 0;
	damage = ((100/(double)(100+e->getDef()))*this->getAtk()) * -1;	//DAMAGE FUNCTION AS SPECIFIED

	std::string tmp, tmp2;
	std::stringstream ss;
	ss << damage*(-1);
	tmp = ss.str();
	ss.str(std::string());
	ss << e->getChar();	//PRETTY PRINTING STUFF
	tmp2 = ss.str();

	this->action = "PC deals 1 damage to " + tmp2 + " (" +  tmp + " HP)";

	if(damage + e->getHP() <= 0)
		e->changeStats(e->getHP() * -1, 0,0);
	else
		e->changeStats(damage,0,0);


	if(e->enemyDead())	//IF ENEMY KILLED..
	{
		std::string s = ". PC has slain " + e->getRace();
		int eX = e->getX();
		int eY = e->getY();
		if(e->getChar() == 'M')
		{
			if(e->getMoveable()) e->toggleMoveable();	//RENDER IT UNMOVABLE
			e->setHostility(false);	//NON-HOSTILE
			Treasure *mHoard = new Treasure(this, eX, eY, e->getDropAmount(), true);	//FOR MERCHANTS...REPLACE WITH HOARD
			int currCh=-1;
			for (int i = 0; i < 5; i++){
				if(fl->ch[i]->insideChamber(eX, eY)) {
					currCh = i;
					break;
				}
			}
			fl->ch[currCh]->addTreasure(mHoard);	//PLACE HOARD IN CHAMBER
			Entity * old = fl->replace(mHoard, eX, eY, true);	//REPLACE/..
		}
		else if(e->getChar() == 'D')
		{
			Entity * empty = new Entity(eX, eY);	//REPLACE DEAD DRAG WITH EMPTY TILE
			Entity * old = fl->replace(empty, eX, eY, true);
			if(e->getMoveable()) e->toggleMoveable();	//SAME AS MERCHANT
			e->setHostility(false);
		}
		else
		{
			pickUpGold(e->getDropAmount());	// PICK UP THE GOLD FROM EVERY OTHER ENEMY UPON DEATH
			Entity * empty = new Entity(eX, eY);	//SAME AS DRAG AND MERCH
			Entity * old = fl->replace(empty, eX, eY, true);
			if(e->getMoveable()) e->toggleMoveable();
			e->setHostility(false);
		}
		
	
		modifyAction(s);
	}
}

void Elf::usePotion(potAtk * pot){	//AS DESCRIBED ABOVE..VISITOR PATTERN
	int val = (pot->getPositive()) ? -5: 5;
	if(this->getAtk() + val < 0)
		changeStats(0, this->getBaseAtk() - this->getAtk(), 0);
	else
		changeStats(0,val,0);
	int i = pot->getPositive() ? 1 : 4;
	seenBefore[i] = true;
}
void Elf::usePotion(potDef * pot){
	int val = (pot->getPositive()) ? -5: 5;
	if(this->getDef() + val < 0)
		changeStats(0, 0, this->getBaseDef() - this->getDef());
	else
		changeStats(0,0,val);
	int i = pot->getPositive() ? 2 : 5;
	seenBefore[i] = true;
}
void Elf::usePotion(potHP * pot){
//if its neg then poison...
	int val = (pot->getPositive()) ? -1: 10;
	if(getHP()+val <= getBaseHP())
		changeStats(val,0,0);
	else
		changeStats(getBaseHP()-getHP(), 0, 0);
	int i = pot->getPositive() ? 0 : 3;
	seenBefore[i] = true;
}
void Dwarf::pickUpGold(int value){
	value *= 2;
	gold += value;
}
void Orc::pickUpGold(int value){
	value /= 2;
	gold += value;
}

std::string checkOBR(Floor *f, Player *p)	//CHECK IF IN ONE BLOCK RADIUS
{
	// 0 North
	// 1 North-East
	// 2 East
	// 3 South-East
	// 4 South
	// 5 South-West
	// 6 West
	// 7 North-West

	int directionX[8] = {0, -1, -1,  -1,  0, 1, 1, 1};
	int directionY[8] = {-1, -1, 0, 1, 1, 1,  0,  -1};
	int pos = 0;
	std::string s;

	for(int i=0; i<8; ++i)
	{
		pos = ((p->getY()+directionY[i]) * f->getWidth()) + (p->getX()+directionX[i]);
		if(f->ent->at(pos)->getType() == "character")
		{
			s = " and sees a " + static_cast<Enemy *>(f->ent->at(pos))->getRace();
			p->modifyAction(s);
		}
		else if(f->ent->at(pos)->getChar() == 'P')
		{
			std::string s = static_cast<Potion *>(f->ent->at(pos))->getPotName();
			bool execute = false;

			if(s=="RH")
				execute = p->getSeenBeforeAt(0);
			else if(s=="BA")
				execute = p->getSeenBeforeAt(1);
			else if(s=="BD")
				execute = p->getSeenBeforeAt(2);
			else if(s=="PH")
				execute = p->getSeenBeforeAt(3);
			else if(s=="WA")
				execute = p->getSeenBeforeAt(4);
			else if(s=="WD")
				execute = p->getSeenBeforeAt(5);

			if(execute)
				s = " and sees a " + static_cast<Potion *>(f->ent->at(pos))->getPotName();
			else
				s = " and sees an unknown potion.";

			p->modifyAction(s);
		}
	}
} 	

std::string moveHelper(int & deltaX, int & deltaY, std::string move, Player *p){
	std::string s = "";
	if (move == "no") {
		deltaY--;
		s = "PC moves North";
	} else if (move == "so") {
		deltaY++;
		s = "PC moves South";
	} else if (move == "ea") {
		deltaX--;
		s = "PC moves East";
	} else if (move == "we") {
		deltaX++;
		s = "PC moves West";
	} else if (move == "ne") {
		deltaY--;
		deltaX--;
		s = "PC moves North-East";
	} else if (move == "nw") {
		deltaY--;
		deltaX++;
		s = "PC moves North-West";
	} else if (move == "se") {
		deltaY++;
		deltaX--;
		s = "PC moves South-East";
	} else if (move == "sw") {
		deltaY++;
		deltaX++;
		s = "PC moves South-West";
	}
	return s;
}

void Player::move(std::string move){
	fl = getFloor();
	int deltaX, deltaY;
	deltaX = deltaY = 0;
	this->action = moveHelper(deltaX, deltaY, move, this);
	if (fl->validMove(getX()+deltaX, getY()+deltaY, true)) {
		Entity * tmp;
		if (oldTile != NULL) tmp = fl->replace(this, getX()+deltaX, getY()+deltaY, false, oldTile);	
		else tmp = fl->replace(this, getX()+deltaX, getY()+deltaY, false);
		if(tmp){
			if(tmp->getType() == "passageway" || tmp->getType() == "doorway") oldTile = tmp; 
			else {
				oldTile = NULL;
				delete tmp;
			}
		} else {
			oldTile = NULL;
		}
	} else {
		this->action = "";
	}
	checkOBR(fl, this);
}
