#include "item.h"

item::item()
{
	M = glm::mat4(1.0f);
	glGenVertexArrays(1, &vao);
}

item::item(int vertex)
{
	M = glm::mat4(1.0f);
	glGenVertexArrays(1, &vao); 
	vertexCount = vertex;

}


item::~item()
{
	glDeleteVertexArrays(1, &vao); //UsuniÍcie vao
}

void item::nextFrame()
{
}


