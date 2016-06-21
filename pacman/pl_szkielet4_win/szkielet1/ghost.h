#pragma once
#include "item.h"
class ghost :
	public item
{
public:
	ghost();
	~ghost();
	void gotoXY(point x);
	//void changePosition();
	//enum state
	//void nextFrame();
};

