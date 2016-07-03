#ifndef ITEM_H
#define ITEM_H

#include "map.h"
//#include "config.h"
#include "point.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace glm;
using namespace std;
class item
{
public:
	GLuint vao;
	GLuint tex;

	point pos;
	point start;
	glm::mat4 M;
	static int dead;//je�li pacman w�a�nie umar� to tu 1
	int vertexCount;
	float width;
	float height;

	int t;
	int t_max;
	float shine;

	item();
	item(int vertex, float w, float h);
	virtual ~item();
	virtual void nextFrame() ;
	virtual void changePosition(map *cMap, int &c);
	bool collisionCheck(map *cMap);

};

#endif

