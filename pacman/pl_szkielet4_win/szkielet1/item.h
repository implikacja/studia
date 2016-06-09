#ifndef ITEM_H
#define ITEM_H


#include "point.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace glm;
class item
{
public:
	GLuint vao;
	point pos;
	glm::mat4 M;
	int vertexCount;

	item();
	item(int vertex);
	virtual ~item();
	virtual void nextFrame() ;

};

#endif

