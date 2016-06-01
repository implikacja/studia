#pragma once

#include "includes.h"
#include <vector>
using namespace glm;
class item;
class map;
class world
{
public:
	std::vector <item *> itemList;
	item *wall;
	item *floor;
	item *coin;
	map* cMap;
	glm::mat4 P;
	glm::mat4 V;

	world();
	~world();	
	void drawScene(GLFWwindow* window, GLuint vao, ShaderProgram *shaderProgram);
	void drawScene2d(GLFWwindow* window, GLuint vao2d, ShaderProgram *shaderProgram);
	void drawObject(GLuint vao, ShaderProgram *shaderProgram, mat4 M);

};

