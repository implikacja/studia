#pragma once

#include "includes.h"
#include <vector>
class item;
class map;
class world
{
public:
	std::vector <item *> itemList;
	item *a;
	map* cMap;

	world();
	~world();	
	void world::drawScene(GLFWwindow* window, GLuint vao, ShaderProgram *shaderProgram);
};

