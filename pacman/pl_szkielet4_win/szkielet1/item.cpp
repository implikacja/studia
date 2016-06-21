#include "item.h"

item::item()
{
	M = glm::mat4(1.0f);
	glGenVertexArrays(1, &vao);
	speed = 0.01;
	width = 1;
	height = 1;
}

item::item(int vertex, float w, float h)
{
	M = glm::mat4(1.0f);
	glGenVertexArrays(1, &vao); 
	width = w;
	height = h;
	vertexCount = vertex;
	speed = 0.01;

}


item::~item()
{
	glDeleteVertexArrays(1, &vao); //Usuniêcie vao
}

void item::nextFrame()
{
}

void item::changePosition()
{

}

bool item::collisionCheck()
{
	//if(pos.x<)
}


