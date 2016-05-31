#pragma once

#include "includes.h"
#include "point.h"
using namespace glm;
class item
{
public:
	point pos;
	glm::mat4 mM;

	item();
	~item();
	void drawObject(GLuint vao, ShaderProgram *shaderProgram, mat4 mP, mat4 mV);
};

