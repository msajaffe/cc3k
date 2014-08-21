#include <string>
#include <iostream>
#include <sstream>
#include "floor.h"
#include "treasure.h"
#include "chamber.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
Floor *Floor::instance = 0;	// Instance is orignally null
using namespace std;
Player * Floor::exitLevel(Player * p, std::string race){	//called at new level or exit game
	if(currentFloor == 6) win=true;		//if finished level 5 then go to win state
	if (!win){
		Entity * empty = new Entity(p->getX(), p->getY());	//replace player class to empty
		replace(empty, p->getX(), p->getY(), true);
	}
	for(int i = 0; i < 5; i++){
		ch[i]->atExit(this); //return to original state
	}
	if(!win || race != "quit") p = generate(p, race);	//if not quit or win then generate new floor
	return p;
}
Floor::Floor(int length, int width): ent(new std::vector<Entity *>), length(length), width(width), currentFloor(1){
	td = new TextDisplay(length, width);	//ctor called once since this is singleton
	ch = new Chamber *[5];
		for (int i = 0; i < 5; i++){
		 ch[i] = new Chamber();
	}
	win = false;
}
Floor * Floor::getInstance(int length, int width) {
	if (!instance) {
		instance = new Floor(length, width);
	}
	return instance;
}
Floor * Floor::getInstance() {
  return instance;
}
void Floor::notify(Entity * e){
    if(ent->size() <= (length*width - 1)) { 
		ent->push_back(e);
	}
	td->notify(e->getX(), e->getY(), e->getChar());
}
Entity * Floor::replace(Entity * e, int x, int y, bool newEnt, Entity * old){	//put Entity e in position (x,y). Turns the old position to type empty
	//ALREADY CHECKED IF VALID MOVE
	int pos2 = y*width + x;		//desired position to move to
	Entity * tmp = &(*ent->at(pos2));	//entity that already exists at desired positon
	if (newEnt){	//if new entity then just replace desired positon
		ent->at(pos2) = e;
		notify(e);
		return tmp;//return replaced tile
	}
	int pos1 = e->getY()*width + e->getX();	//current position

	if (ent->at(pos2)->getType() == "stairway") {	//if tryna replace stairway then just and go into new level
		Player * p = static_cast <Player *> (e);
		exitLevel(p);
		++currentFloor;
		return 0;
	}
	if (old != NULL) {	//algorithm to keep the an old image in place as opposed to turning it into empty (like doorways and stuff)
		ent->at(pos1) = new Entity(e->getX(), e->getY(), old->getChar(), old->getType());
		delete old;
	}
	else ent->at(pos1) = new Entity(e->getX(), e->getY());	//if the old image is just empty, then replace old tile with empty
	e->setStats(x, y, e->getChar(), e->getType());	//change the stats of entity to desired tile
	ent->at(pos2) = e;
	notify(e);	//change text display
	notify(ent->at(pos1));
	return tmp; //return replaced tile
}
bool Floor::validMove(int x, int y, bool player){	//The only time moves arent valid are if the tile is a wall(including passageways) or a character?
	int pos = y*width + x;
	std::string type = ent->at(pos)->getType();
	if (type == "doorway" && !player) return false; 
	if (type == "wall" || type == "character") return false;
	if (type == "item"){	//if the move is to an item, then that item must be available
		if (!player || ent->at(pos)->getChar()=='P') return false;
		Treasure * kk = static_cast <Treasure *> (ent->at(pos));	//if item and not potion then it must be treasure
		if (kk->getAvailable()) kk->effect(); 
		else return false;
	} else if(!player && (type == "passageway" || type == "stairway" || type == "doorway")) return false;
	return true;

}

void Floor::draw(Player *p, bool won){	//simple draw function
	if(!won)
	{
		std::string s;
		std::stringstream ss;
		ss << p->getGoldAmount();
		s = ss.str();

		std::cout << *td << std::endl;
		
		std::cout << "Race: " << p->getRace() << " Gold: " << p->getGoldAmount();
		
		for(int i=0; i<(width - 6 - 7 - p->getRace().length() - s.length() - 10); ++i)
			std::cout << " "; 

		std::cout << "Level: " << this->currentFloor << std::endl;
		std::cout << "HP: " << p->getHP() << std::endl;
		std::cout << "Atk: " << p->getAtk() << std::endl;
		std::cout << "Def: " << p->getDef() << std::endl;
		if(p->getActionMade())
		{
			std::string action = (p->getAction() == "") ? "Invalid move.": p->getAction() + ".";
			std::cout << "Action: " << action << std::endl;
		}

		p->newAction("");
	}
	else
	{
		std::cout << "Congratulations you have beaten the game!" << std::endl;
		std::cout << "Your score was: " << p->getScore();
		std::cout << "Made by: Nerman Nicholas and Sibtain Jafferi" << std::endl;
	}
}

void Floor::initChambers(){	//initialize all chambers
int chCount = 0;
	for (int y = 0; y < length; y++){
		for (int x = 0; x < width; x++){
			int pos = y*width + x;
			if (ent->at(pos)->getChar() == '.'){
				if(chCount!=0){
					int tmp = 0;
					for (int i = 0; i < chCount; i++){
						if(!ch[i]->insideChamber(ent->at(pos)->getX(), ent->at(pos)->getY())) tmp++;
					}
					if (tmp == chCount) {
						fillChamber(ch[chCount], ent->at(pos));
						chCount++;	
					}
				} else {
					fillChamber(ch[chCount], ent->at(pos));
					chCount++;	
				}
			}
		}
	}
}
void Floor::fillChamber(Chamber * ch, Entity * tile){	//fill one chamber
	int x = tile->getX(); int y = tile->getY(); 
	ch->addTile(x, y);
	int pos = y*width + (x+1);
	std::string s = ent->at(pos)->getType();
	if ((s=="empty" || s=="doorway") && !ch->insideChamber(x + 1, y)){
		fillChamber(ch, ent->at(pos));
	} 
	pos = (y+1)*width + x;
	s = ent->at(pos)->getType();
	if ((s=="empty" || s=="doorway") && !ch->insideChamber(x, y + 1)){
		fillChamber(ch, ent->at(pos));
	}
	pos = (y-1)*width + x;
	s = ent->at(pos)->getType();
	if ((s=="empty" || s=="doorway") && !ch->insideChamber(x, y - 1)){
		fillChamber(ch, ent->at(pos));
	}
	pos = y*width + (x-1);
	s = ent->at(pos)->getType();
	if ((s=="empty" || s=="doorway") && !ch->insideChamber(x - 1, y)){
		fillChamber(ch, ent->at(pos));
	}
}

int Floor::turn(Player * p){	//fulfill one turn 
	for (int i = 0; i < 5; i++){
		int playerDead = ch[i]->enemyTurn(p);
		if (playerDead) return playerDead;
		ch[i]->potionTurn(this);
	}
	return 0;
}

Player * Floor::generate(Player * p, string playerRace){	//generation
	int rand(void);
	int playerChamber = rand() % 5;
	int randSpot;
	pair<int, int> playerPos;
	int pos;
	do {
		randSpot = rand() % ch[playerChamber]->getMap()->size();
		playerPos = ch[playerChamber]->getMap()->at(randSpot);
		pos = playerPos.second * width + playerPos.first;
	} while (ent->at(pos)->getType() != "empty");
	if(playerRace != ""){
		if(playerRace=="o")
			p = new Orc(playerPos.first, playerPos.second);
		else if(playerRace=="e")
			p = new Elf(playerPos.first, playerPos.second);
		else if(playerRace=="d")
			p = new Dwarf(playerPos.first, playerPos.second);
		else
			p = new Human(playerPos.first, playerPos.second);
	} else {
		p->setStats(playerPos.first, playerPos.second, '@', "character");
	}
	p->add();
	int stairChamber;
	pair<int, int> stairPos;
	do {
		stairChamber = rand() % 5;
		randSpot = rand() % ch[stairChamber]->getMap()->size();
		stairPos = ch[stairChamber]->getMap()->at(randSpot);
		pos = stairPos.second * width + stairPos.first;
	} while(stairChamber == playerChamber || ent->at(pos)->getType() != "empty");

	Entity * stairs = new Entity(stairPos.first, stairPos.second, '/', "stairway");
	ch[stairChamber]->setStairs(stairs);
	stairs->add();
	for (int i = 0; i < 10; i++){	//POTIONS
		int potChamber = rand() % 5;
		randSpot = rand() % ch[potChamber]->getMap()->size();		
		pair<int, int> potPos = ch[potChamber]->getMap()->at(randSpot);
		pos = potPos.second * width + potPos.first;
		while(ent->at(pos)->getType() != "empty"){
			randSpot = rand() % ch[potChamber]->getMap()->size();
			pair<int, int> potPos = ch[potChamber]->getMap()->at(randSpot);
			pos = potPos.second * width + potPos.first;			
		}
		Potion * pot;
		int potType = rand() % 6;
		switch (potType){
			case 0: {
				pot = new potAtk(p, true, potPos.first, potPos.second, 'P');
				break;
			} case 1: {
				pot = new potAtk(p, false, potPos.first, potPos.second, 'P');
				break;
			} case 2: {
				pot = new potDef(p, true, potPos.first, potPos.second, 'P');
				break;
			} case 3: {
				pot = new potDef(p, false, potPos.first, potPos.second, 'P');
				break;
			} case 4: {
				pot = new potHP(p, true, potPos.first, potPos.second, 'P');
				break;
			} default: {
				pot = new potHP(p, false, potPos.first, potPos.second);
				break;
			}
		}
		pot->add();
		ch[potChamber]->addPot(pot);
	}
	Chamber * drag = new Chamber();
	for (int i = 0; i < 10; i++){	
		int treasureChamber = rand() % 5;
		randSpot = rand() % ch[treasureChamber]->getMap()->size();		
		pair<int, int> treasurePos = ch[treasureChamber]->getMap()->at(randSpot);
		pos = treasurePos.second * width + treasurePos.first;
		while(ent->at(pos)->getType() != "empty"){
			randSpot = rand() % ch[treasureChamber]->getMap()->size();
			pair<int, int> treasurePos = ch[treasureChamber]->getMap()->at(randSpot); 
			pos = treasurePos.second * width + treasurePos.first;			
		}
		Treasure * treasure;
		int treasureType = rand() % 8;
		if (treasureType < 5){
			treasure = new Treasure(p, treasurePos.first, treasurePos.second);
		} else if(treasureType < 7){
			treasure = new Treasure(p, treasurePos.first, treasurePos.second, 2, true);
		} else if (treasureType == 7){
		//drag
			treasure = new Treasure(p, treasurePos.first, treasurePos.second, 6, false);
			drag->addTile(treasurePos.first, treasurePos.second);
		}
		treasure->add();
		ch[treasureChamber]->addTreasure(treasure);
	}
	for (int i = 0; i < 20; i++){	
		int enemyChamber = rand() % 5;
		randSpot = rand() % ch[enemyChamber]->getMap()->size();		
		pair<int, int> enemyPos = ch[enemyChamber]->getMap()->at(randSpot);
		pos = enemyPos.second * width + enemyPos.first;
		while(ent->at(pos)->getType() != "empty"){
			randSpot = rand() % ch[enemyChamber]->getMap()->size();
			pair<int, int> enemyPos = ch[enemyChamber]->getMap()->at(randSpot); 
			pos = enemyPos.second * width + enemyPos.first;			
		}
		Enemy * enemy;
		int enemyType = rand() % 18;
		if (enemyType < 5){
			enemy = new Goblin(enemyPos.first, enemyPos.second);
		} else if(enemyType < 9){
			enemy = new Werewolf(enemyPos.first, enemyPos.second);
		} else if (enemyType < 12){
			enemy = new Vampire(enemyPos.first, enemyPos.second);
		} else if (enemyType < 14){
			enemy = new Troll(enemyPos.first, enemyPos.second);
		} else if (enemyType < 16){
			enemy = new Phoenix(enemyPos.first, enemyPos.second);
		} else if (enemyType < 18){
			enemy = new Merchant(enemyPos.first, enemyPos.second);
		}
		enemy->add();
		ch[enemyChamber]->addEnemy(enemy);
	}
	for (int i = 0; i < drag->getMap()->size(); i++){
		int xdrag = drag->getMap()->at(i).first;
		int ydrag = drag->getMap()->at(i).second;
		pos = ydrag*width + xdrag;
		Treasure * t = static_cast <Treasure *> (ent->at(pos));
		Enemy * enemy = new Dragon(xdrag, ydrag, t);
		enemy->toggleMoveable();
		enemy->move();
		t->add();
		int currentCh = 0;
		for(int i =0; i < 5; i++){
			if(ch[i]->insideChamber(xdrag, ydrag)) { 
				currentCh = i;
				break;
			}
		}
		enemy->toggleMoveable();
		ch[currentCh]->addEnemy(enemy);
	}
	return p;
}
