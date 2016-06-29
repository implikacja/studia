#ifndef PACMAN_H
#define PACMAN_H

#include "item.h"
#include "config.h"


class pacman :
	public item
{
public:
	char lastDir;
	pacman();
	pacman(int vertex, map *cMap);
	~pacman();
	void changePosition(map *cMap, int c);
	void nextFrame();
	bool collisionCheck(map *cMap);
};

#endif