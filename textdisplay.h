#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>
class TextDisplay {
char **theDisplay;
const int length, width;
public:
	TextDisplay(int, int);
	void notify(int x, int y, char ch); //gets notified by entities of state change
	~TextDisplay(){	//destroy array of characters on delete
		for (int i = 0; i < length*width; i++){
			delete theDisplay[i];
		}
		delete [] theDisplay;
	}
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
