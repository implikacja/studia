#pragma once
#include "includes.h"
#include <vector>

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
	world *w2d;
	world *w3d;
	GLFWwindow* window; 




	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mainloop();
	static bool loadObj(const char * path, std::vector < glm::vec4 > & out_vertices, std::vector < glm::vec4 > & out_normals);
	static bool loadObj(const char * path, float *& out_vertices, float *& out_normals, int* indeks);
};

