#pragma once
#include "includes.h"

class world;
class config
{
public:
	//Uchwyty na VAO i bufory wierzcho³ków
	GLuint vao;
	GLuint bufVertices; //Uchwyt na bufor VBO przechowuj¹cy tablicê wspó³rzêdnych wierzcho³ków
	GLuint bufColors;  //Uchwyt na bufor VBO przechowuj¹cy tablicê kolorów
	GLuint bufNormals; //Uchwyt na bufor VBO przechowuj¹cy tablickê wektorów normalnych
	GLFWwindow* window; //WskaŸnik na obiekt reprezentuj¹cy okno
	//Uchwyty na shadery
	ShaderProgram *shaderProgram; //WskaŸnik na obiekt reprezentuj¹cy program cieniuj¹cy.
	config();
	~config();
	GLuint makeBuffer(void *data, int vertexCount, int vertexSize);
	void assignVBOtoAttribute(ShaderProgram *shaderProgram, char* attributeName, GLuint bufVBO, int vertexSize);
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mainloop(world w);
};

