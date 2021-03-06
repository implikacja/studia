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
#include "ghost.h"
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
	item *text;
	vec4 textColor;
	map* cMap;
	int coins;
	int hp;
	glm::mat4 P;
	glm::mat4 V;
	int timer;
    ShaderProgram *shaderProgram; //Wskaźnik na obiekt reprezentujący program cieniujący.
	ShaderProgram *shaderProgramA;
	ShaderProgram *shaderProgramC;
	GLuint bufVertices;
	GLuint bufColors;
	GLuint bufNormals;
	GLuint bufUvs;
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;

	world();
	world(bool mode);
	~world();	
	GLuint makeBuffer(void *data, int vertexCount, int vertexSize);
	void assignVBOtoAttribute(ShaderProgram *shaderProgram, char* attributeName, GLuint bufVBO, int vertexSize);
	void createVAO(item* i, float* vertices, float* uvs, float* normals, int indeks);
	void createVAO(item* i, float* vertices1, float* vertices2, float* uvs, float* normals1, float* normals2, int indeks);
	void drawScene(GLFWwindow* window);
	void drawObject(GLuint vao, mat4 M, int vertexCount);
	void drawObject(GLuint vao, GLuint tex, float s, mat4 M, int vertexCount);
	void drawObject(GLuint vao, GLuint tex, float s, float t, mat4 M, int vertexCount);
	void drawObject(GLuint vao, float t, mat4 M, int vertexCount);
	void drawMap2d(GLFWwindow* window, mat4 V);
	void drawMap3d(GLFWwindow* window, mat4 V);
	void changeCamera();
	void loadText(const char* path, vec4 color);
	glm::vec3 world::setLight0();
	glm::vec3 world::setLight1();
	void logic();

	void testowanie(const char* path,float* vertices, float* uvs, float* normals, int indeks);
};

