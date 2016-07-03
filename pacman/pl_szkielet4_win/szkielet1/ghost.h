#pragma once
#include "item.h"
#include "config.h"
class ghost :
	public item
{
public:
	int nr;
	vector<pair<int, int>>road;
	ghost();
	ghost(int vertex, map *cMap, int n);
	~ghost();
	void gotoXY(int x, int y, map *cMap);
	void changePosition(map *cMap, int c);
	
	//enum state
	//void nextFrame();
};

