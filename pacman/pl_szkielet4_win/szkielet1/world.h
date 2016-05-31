#pragma once

#include "includes.h"
#include <vector>
class item;
class world
{
public:
	std::vector <item *> itemList;
	//item *itemList;
	item *a;
	world();
	~world();	
	void world::drawScene(GLFWwindow* window, GLuint vao, ShaderProgram *shaderProgram);

};

