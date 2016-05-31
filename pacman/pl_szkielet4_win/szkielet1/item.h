#pragma once

#include "includes.h"
#include "point.h"
using namespace glm;
class item
{
public:
	point pos;
	mat4 P;
	mat4 V;
	mat4 M;

	item();
	~item();
	void drawObject(GLuint vao, ShaderProgram *shaderProgram, mat4 mP, mat4 mV, mat4 mM);
};

