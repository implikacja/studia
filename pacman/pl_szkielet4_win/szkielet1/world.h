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
	glm::mat4 P;
	glm::mat4 V;

	world();
	~world();	
	void drawScene(GLFWwindow* window, GLuint vao, ShaderProgram *shaderProgram);
	void drawScene2d(GLFWwindow* window, GLuint vao2d, ShaderProgram *shaderProgram);
};

