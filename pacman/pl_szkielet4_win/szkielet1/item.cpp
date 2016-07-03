#include "item.h"

int item::dead = 0;
item::item()
{
	M = glm::mat4(1.0f);
	glGenVertexArrays(1, &vao);
	width = 1;
	height = 1;
	t = 0;
	t_max = 0;
}

item::item(int vertex, float w, float h)
{
	M = glm::mat4(1.0f);
	glGenVertexArrays(1, &vao); 
	width = w;
	height = h;
	vertexCount = vertex;
	t = 0;
	t_max = 0;
}


item::~item()
{
	glDeleteVertexArrays(1, &vao); //Usuniêcie vao
}

void item::nextFrame()
{
	t++;
	if (t > t_max) t = 0;
}

void item::changePosition(map *cMap, int &c)
{

}

bool item::collisionCheck(map *cMap)
{

}


