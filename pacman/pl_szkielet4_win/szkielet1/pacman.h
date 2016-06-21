#ifndef PACMAN_H
#define PACMAN_H

#include "item.h"
#include "map.h"
#include "config.h"

class pacman :
	public item
{
public:
	pacman();
	pacman(int vertex, map *cMap);
	~pacman();
	void changePosition();
	void nextFrame();
};

#endif