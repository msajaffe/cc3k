#include "textdisplay.h"
#include <iostream>
TextDisplay::TextDisplay(int len, int wid): length(len), width(wid) {
	theDisplay = new char * [length*width];	//make and initialize 2d array of characters
	for (int i = 0; i < length*width; i++){
		 theDisplay[i] = new char(' ');
	}
}
void TextDisplay::notify(int x, int y, char ch){
	int pos = y*width + x;	//2d position converted to 1d
	if (pos != 2000) *theDisplay[pos] = ch; //CHANGE LATER
}

std::ostream & operator<<(std::ostream &out, const TextDisplay &td){
	
	for (int r = 0; r < td.length; r++){
		for (int c = 0; c < td.width; c++){
			int pos = r*td.width + c;
			out << *td.theDisplay[pos];	//out each individual character in row
		}
		out << std::endl; //new line after each row
	}
	return out;
}