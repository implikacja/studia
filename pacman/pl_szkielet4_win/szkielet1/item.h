#pragma once

#include "includes.h"
using namespace glm;
class item
{
public:
	int x;
	item();
	~item();
	void drawObject(GLuint vao, ShaderProgram *shaderProgram, mat4 mP, mat4 mV, mat4 mM);
};

