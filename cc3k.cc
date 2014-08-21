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

int interperate(/*string filename,*/ Floor & fl){
	string line, type;
	int y = 0;
	int width;
	ifstream myfile ("defaultLevel.txt");
	if (myfile.is_open()) {
    while (getline(myfile,line)) {
		width = line.length();
		char cstr[width+1];
		strcpy(cstr, line.c_str());
		for (int x = 0; x < width; x++){
			int pos = y*width + x;
			if (cstr[x] == '|' || cstr[x] == '-') { 
				type = "wall";
			} else if(cstr[x] == ' ') {
				type = "wall";
			}else if (cstr[x] == '#') {
				type = "passageway";
			} else if (cstr[x] == '.') {
				type = "empty";
			} else if (cstr[x] == '+') {
				type = "doorway";
			}
			Entity * tmp = new Entity(x, y, cstr[x], type);
			fl.notify(tmp);
		}
		y++;
	}
    myfile.close();
  }
  return y;
}

int main(){
	int length = 25;
	int width = 80;
	Floor *f = Floor::getInstance(length, width);
	interperate(*f);
	f->initChambers();
	Player * h = 0;
	
	string s;
	cout << "Enter your race (\"o\" for orc | \"d\" for dwarf | \"e\" for elf | and anything else for human): " << endl;
	
	cin >> s;
	h = f->generate(h, s);
	f->draw(h);
	int pos = 0;
	cout << "Enter: ";

	while (cin >> s){	//interperator
		cout << endl;

		if(f->getWinState())
		{
			f->draw(h, true);
			f->exitLevel(h);
			delete f;
			exit(0);
		}
		if(s == "no" || s == "ne" || s == "ea" || s == "se" || s == "so" || s == "sw" || s == "we" || s == "nw")
		{
			h->setActionMade(true);
			h->move(s);
		}
		else if(s == "a")
		{
			cin >> s;
			h->setActionMade(true);
			if(s=="no")
				pos = (h->getY() -1)*width + h->getX(); 
			else if(s=="ne")
				pos = (h->getY() -1)*width + h->getX() -1; 
			else if(s=="ea")
				pos = (h->getY())*width + h->getX()-1; 
			else if(s=="se")
				pos = (h->getY() +1)*width + h->getX()-1; 
			else if(s=="so")
				pos = (h->getY() +1)*width + h->getX(); 
			else if(s=="sw")
				pos = (h->getY() +1)*width + h->getX()+1; 
			else if(s=="we")
				pos = (h->getY())*width + h->getX()+1; 
			else
				pos = (h->getY()-1)*width + h->getX()+1; 

			if(f->ent->at(pos)->getType() == "character")
				h->attack(static_cast<Enemy *>(f->ent->at(pos)),s);
		}
		else if(s == "u")
		{
			cin >> s;
			h->setActionMade(true);
			if(s=="no")
				pos = (h->getY() -1)*width + h->getX();
			else if(s=="ne")
				pos = (h->getY() -1)*width + h->getX() -1;
			else if(s=="ea")
				pos = (h->getY())*width + h->getX()-1; 
			else if(s=="se")
				pos = (h->getY() +1)*width + h->getX()-1; 
			else if(s=="so")
				pos = (h->getY() +1)*width + h->getX(); 
			else if(s=="sw")
				pos = (h->getY() +1)*width + h->getX()+1; 
			else if(s=="we")
				pos = (h->getY())*width + h->getX()+1; 
			else if(s=="nw")
				pos = (h->getY()-1)*width + h->getX()+1; 

			if(f->ent->at(pos)->getChar() == 'P')
					static_cast <Potion *>(f->ent->at(pos))->use();
		}
		else if(s == "r")
		{
			
			h->setActionMade(true);
			cout << "Enter your race (\"o\" for orc | \"d\" for dwarf | \"e\" for elf | and anything else for human): " << endl;
			h->setGold(0);
			cin >> s;
			//delete h;
			h = f->exitLevel(h, s);

		}
		else if(s == "q")
		{
			h->setActionMade(true);
			f->exitLevel(h, "quit");
		//	delete f;
			exit(0);
		}
		else
		{
			h->setActionMade(false);
			//do nothing if they enter gibberish
		}

		int playerDead = f->turn(h);
		if (playerDead) return 0; //end screen.
		f->draw(h);
		
		cout << "Enter: ";
	}
}


