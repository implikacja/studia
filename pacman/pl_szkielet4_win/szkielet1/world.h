#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "shaderprogram.h"
#include "pacman.h"
#include "models.h"
#include "map.h"
#include "config.h"
#include "constants.h"
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
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;

	world();
	world(bool mode);
	~world();	
	GLuint makeBuffer(void *data, int vertexCount, int vertexSize);
	void assignVBOtoAttribute(ShaderProgram *shaderProgram, char* attributeName, GLuint bufVBO, int vertexSize);
	void drawScene(GLFWwindow* window);
	void drawObject(GLuint vao, mat4 M, int vertexCount);
	void drawMap2d(GLFWwindow* window, mat4 V);

};

