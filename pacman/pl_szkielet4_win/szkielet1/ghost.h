#pragma once
#include "item.h"
#include "config.h"
#include <time.h>
class ghost :
	public item
{
public:
	int nr;
	vector<pair<int, int>>road;
	vector<pair<int, int>>vertex;
	ghost();
	ghost(int vertex, map *cMap, int n);
	~ghost();
	void gotoXY(int x, int y, map *cMap);
	void changePosition(map *cMap, int &c);
	
	//enum state
	//void nextFrame();
};

