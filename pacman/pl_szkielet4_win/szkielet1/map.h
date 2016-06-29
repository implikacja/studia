#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
class map
{
public:
	int w;
	int h;
	char** m;
	~map();
	map();
};

#endif