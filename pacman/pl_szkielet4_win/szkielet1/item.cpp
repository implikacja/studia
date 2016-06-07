#include "item.h"

item::item()
{

}

item::item(int vertex)
{
	M = glm::mat4(1.0f);
	glGenVertexArrays(1, &vao); 
	vertexCount = vertex;

}


item::~item()
{
	glDeleteVertexArrays(1, &vao); //Usuniêcie vao
}


