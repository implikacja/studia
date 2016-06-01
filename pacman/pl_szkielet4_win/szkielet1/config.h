#pragma once
#include "includes.h"
#include <vector>

class world;
class config
{
public:
	bool mode3d;
	//Uchwyty na VAO i bufory wierzcho³ków
	GLuint vao[5];
	GLuint vao2d[7];
	GLuint bufVertices[5]; 
	GLuint bufColors[5];  
	GLuint bufNormals[5]; 
	GLuint bufVertices2d[7];  
	GLuint bufColors2d[7];
	GLFWwindow* window; 

	ShaderProgram *shaderProgram; //WskaŸnik na obiekt reprezentuj¹cy program cieniuj¹cy.

	config();
	~config();
	GLuint makeBuffer(void *data, int vertexCount, int vertexSize);
	void assignVBOtoAttribute(ShaderProgram *shaderProgram, char* attributeName, GLuint bufVBO, int vertexSize);
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mainloop(world w);

	bool loadObj(const char * path, std::vector < glm::vec4 > & out_vertices, std::vector < glm::vec4 > & out_normals);
	bool loadObj(const char * path, float *& out_vertices, float *& out_normals, int* indeks);
};

