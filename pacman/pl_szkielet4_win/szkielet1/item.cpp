#include "item.h"
#include "constants.h"

int item::dead = 0;
item::item()
{
	M = glm::mat4(1.0f);
	pM = glm::mat4(0.0f);
	glGenVertexArrays(1, &vao);
	width = 1;
	height = 1;
	t_max = 0;
}

item::item(int vertex, float w, float h)
{
	M = glm::mat4(1.0f);
	pM = glm::mat4(0.0f);
	glGenVertexArrays(1, &vao); 
	width = w;
	height = h;
	vertexCount = vertex;
	t_max = 0;
}


item::~item()
{
	glDeleteVertexArrays(1, &vao); //Usuniêcie vao
	glDeleteTextures(1, &tex);
}

void item::nextFrame()
{
	t++;
	if (t > t_max || M==pM) t = 0;
	//printf("nextFrame: %d\n", t);
}

void item::changePosition(map *cMap, int &c)
{

}

bool item::collisionCheck(map *cMap)
{

}

glm::mat4 item::getRealMatrix()
{
	mat4 m = glm::translate(M,vec3(-0.5f,-0.5f,0.0f));
	if (M != pM && t != 0) m = translateModel(m);
	m = rotateModel(m);
	return m;
}

glm::mat4 item::rotateModel(mat4 m)
{
	switch (pos.direction)
	{
	case 'l':
		return m;
		break;
	case 'r':
		return glm::rotate(m, PI, vec3(0, 0, 1));
		break;
	case 'u':
		return glm::rotate(m, 1.5f*PI, vec3(0, 0, 1));
		break;
	case 'd':
		return glm::rotate(m, 0.5f*PI, vec3(0, 0, 1));
		break;
	default:
		return m;
		break;
	}
}

glm::mat4 item::translateModel(mat4 m)
{
	switch (pos.direction)
	{
	case 'l':
		return glm::translate(m, vec3(1 - (float)t / t_max, 0, 0));
		break;
	case 'r':
		return glm::translate(m, vec3(-1 + (float)t / t_max, 0, 0));
		break;
	case 'u':
		return glm::translate(m, vec3(0, -1 + (float)t / t_max, 0));
		break;
	case 'd':
		return glm::translate(m, vec3(0, 1 - (float)t / t_max, 0));
		break;
	default:
		return M;
		break;
	}
}

float item::getRealX()
{
	if (M == pM || t==0) return pos.x;
	float x = pos.x;
	switch (pos.direction)
	{
	case 'l':
		return x + 1 - (float)t / t_max;
	case 'r':
		return x - 1 + (float)t / t_max;
		break;
	default:
		return x;
		break;
	}
}

float item::getRealY()
{
	if (M == pM || t==0) return pos.y;
	float y = pos.y;
	switch (pos.direction)
	{
	case 'd':
		return y + 1 - (float)t / t_max;
	case 'u':
		return y - 1 + (float)t / t_max;
		break;
	default:
		return y;
		break;
	}
}


