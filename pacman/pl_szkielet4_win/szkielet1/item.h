#pragma once

#include "includes.h"
#include "point.h"
using namespace glm;
class item
{
public:
	GLuint vao;
	point pos;
	glm::mat4 M;
	int vertexCount;
	int nrVao;

	item();
	item(int vertex);
	~item();

};

