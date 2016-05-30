#pragma once

#include "includes.h"

class world
{
public:
	//vector <item*> itemList;
	world();
	~world();	
	void world::drawScene(GLFWwindow* window, GLuint vao, ShaderProgram *shaderProgram);

};

