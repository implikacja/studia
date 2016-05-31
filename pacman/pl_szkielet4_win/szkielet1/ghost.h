#pragma once
#include "item.h"
class ghost :
	public item
{
public:
	ghost();
	~ghost();
	void gotoXY(point x);
	//enum state
	void nextFrame();
};

