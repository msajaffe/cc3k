#include "enemy.h"
#include <cstdlib>
#include <string>
#include <math.h>
#include "treasure.h"
#include "player.h"
#include <iostream>
#include <sstream>
void Enemy::move()
{
	if(moveable)
	{
		f = getFloor();
		int rand(void);
		int newX, newY, direction;
		do
		{
			newX = getX();
			newY = getY();
			direction = rand() % 8; //0 for north
		                            //1 for north-east
		                            //2 for east
		                            //3 for south-east
		                            //4 for south
		                            //5 for south-west
		                            //6 for west
		                            //7 for north-west
			if(direction == 0)
			{
				newY = getY() + 1;
			}
			else if(direction == 1)
			{
				newX = getX() + 1;
				newY = getY() + 1;
			}
			else if(direction == 2)
			{
				newX = getX() + 1;
			}
			else if(direction == 3)
			{
				newX = getX() + 1;
				newY = getY() - 1;
			}
			else if(direction == 4)
				newY = getY() - 1;
			else if(direction ==5)
			{
				newX = getX() - 1;
				newY = getY() - 1;
			}
			else if(direction == 6)
			{
				newX = getX() - 1;
			}
			else
			{
				newX = getX() - 1;
				newY = getY() + 1;
			}
		}
		while(!f->validMove(newX,newY, false));
		Entity * tmp = f->replace(this, newX, newY);
		delete tmp;
	}
}

bool Enemy::inOBR(Entity *target, Entity *e)
{
	if (e==0) {
		Character * c = this;
		e = c;
	}
	if(target->getX() <= (e->getX()+1) && target->getX() >= (e->getX()-1) && target->getY() <= (e->getY()+1) && target->getY() >= (e->getY()-1))
		return true;
	return false;
}

void Enemy::attack(Player *p) {
	int rand (void);
	int damage=0;
	if(inOBR(p, this)) {
		if(checkHostility(p)) {
			int x = rand() % 100;
			std::string s, tmp;
			std::stringstream ss;
			ss << getChar();
			tmp = ss.str();
			ss.str(std::string());
			if(x >= 50) {
				damage = ceil((100/(double)(100+p->getDef()))*this->getAtk()) * -1;
				if(damage + p->getHP() <= 0)
					p->changeStats(p->getHP() * -1, 0,0);
				else
					p->changeStats(damage,0,0);
				std::string tmp2;
				ss << damage*(-1);
				tmp2 = ss.str();
				if(p->getAction() == "" || p->getAction() == "Player character has spawned")
					s = tmp + " deals " + tmp2 + " damage to PC";
				else
					s = ". "+ tmp + " deals " + tmp2 + " damage to PC";
			}
			else s = ". " + tmp + " tries to attack PC, but misses";
			p->modifyAction(s);
		}
	}
}
bool Enemy::enemyDead()
{
	
	if(getHP() <= 0)
		return true; 
	return false;
}

bool Merchant::checkHostility(Player *p){	
	if(p->getAttackedMerchant())
		hostility = true;
	if(enemyDead()) return false;
	return hostility;
}

bool Dragon::checkHostility(Player *p){
	if(inOBR(p, this->dHoard))
		hostility = true;
	else
		hostility = false;
	return hostility;
}

bool Dragon::enemyDead()
{
	if(getHP() <= 0)
	{
		this->dHoard->setAvailability(true);
		this->dHoard = NULL;
		return true;
	}
	
	return false;
}