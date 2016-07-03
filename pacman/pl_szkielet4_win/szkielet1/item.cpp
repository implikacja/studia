#include "item.h"

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
}

void item::nextFrame()
{
	t++;
	if (t > t_max || M==pM) t = 0;
	printf("nextFrame: %d\n", t);
}

void item::changePosition(map *cMap, int &c)
{

}

bool item::collisionCheck(map *cMap)
{

}

glm::mat4 item::getRealMatrix()
{
	if (M == pM || t==0) return M;
	printf("Macierz z drobnym przesuniêciem %d/%d = %f\n",t,t_max,(float)t/t_max);
	glm::mat4 rm;
	switch (pos.direction)
	{
	case 'l':
		rm = glm::translate(M, vec3(1-(float)t/t_max,0,0));
		break;
	case 'r':
		rm = glm::translate(M, vec3(-1+(float)t / t_max, 0, 0));
		break;
	case 'u':
		rm = glm::translate(M, vec3(0,-1+(float)t / t_max, 0));
		break;
	case 'd':
		rm = glm::translate(M, vec3(0,1-(float)t / t_max, 0));
		break;
	default:
		rm = M;
		break;
	}
	return rm;
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


