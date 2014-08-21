#include "item.h"
int Item::add() {
	if(f->validMove(getX(), getY())){
		Entity * tmp = f->replace(this, getX(), getY(), true);
		delete tmp;
		return 0;	//successful add
	}
	return 1;	//unsuccessful
}

