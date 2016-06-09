#ifndef PACMAN_H
#define PACMAN_H

#include "item.h"

class pacman :
	public item
{
public:
	pacman();
	pacman(int vertex);
	~pacman();
	void changePosition(char c);
	void nextFrame();
};

#endif