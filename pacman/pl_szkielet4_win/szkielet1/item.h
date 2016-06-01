#pragma once

#include "includes.h"
#include "point.h"
using namespace glm;
class item
{
public:
	point pos;
	glm::mat4 M;
	int vertexCount;
	int nrVao;

	item();
	~item();

};

