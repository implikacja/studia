#ifndef CONFIG_H
#define CONFIG_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "world.h"

class world;
class config
{
private:
    config();
	config(const config &) = delete;
	config& operator=(const config&) = delete;
	static config *instance;
	static bool instanceFlag;
	~config();
public:
	static config* getInstance()
	{
		if (!instance) instance = new config;
		instanceFlag = true;
		return instance;
	}

	bool mode3d;
	static float width;//szerokoœæ pola
	world *w2d;
	world *w3d;
	GLFWwindow* window; 
	static char c;//odbierane w pacmanie
	static int end;
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mainloop();
	static bool loadObj(const char * path, std::vector < glm::vec4 > & out_vertices, std::vector < glm::vec4 > & out_normals);
	static bool loadObj(const char * path, float *& out_vertices, float *& out_normals, int* indeks);
};

#endif