#pragma once

#include "includes.h"
class item;
class world
{
public:
	//vector <item *> itemList;
	item *itemList;
	item *a;
	world();
	~world();	
	void world::drawScene(GLFWwindow* window, GLuint vao, ShaderProgram *shaderProgram);

};

