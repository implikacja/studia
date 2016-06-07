#pragma once

#include "includes.h"
#include <vector>
using namespace glm;
class item;
class map;
class world
{
public:
	bool mode3d;
	std::vector <item *> itemList;
	item *wall;
	item *floor;
	item *coin;
	map* cMap;
	glm::mat4 P;
	glm::mat4 V;
    ShaderProgram *shaderProgram; //Wskaünik na obiekt reprezentujπcy program cieniujπcy.
	GLuint bufVertices;
	GLuint bufColors;
	GLuint bufNormals;

	world();
	world(bool mode);
	~world();	
	GLuint makeBuffer(void *data, int vertexCount, int vertexSize);
	void assignVBOtoAttribute(ShaderProgram *shaderProgram, char* attributeName, GLuint bufVBO, int vertexSize);
	void drawScene(GLFWwindow* window);
	void drawObject(GLuint vao, mat4 M, int vertexCount);

};

