#include "pacman.h"



pacman::pacman()
{
	//jupi ja jej

}

pacman::pacman(int vertex, map *cMap)
{
	pos.x = -cMap->h / 2;
	pos.y = cMap->h / 2;
	bool flag = 0;
	for (int i = 0; i < cMap->h; i++)
	{
		for (int j = 0; j < cMap->h; j++)
		{
			if (pos.x >= cMap->h / 2)pos.x = -cMap->h / 2;
			if (cMap->m[j][i] == 'p')
			{
				flag = 1;
				break;
			}

		}
		if (flag) break;
	}
	pos.z = 0;
	vertexCount = vertex;
	M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
	pos.direction = 'u';
	width = 1;
	height = 1;
}

pacman::~pacman()
{
}

void pacman::nextFrame()
{/*
	M = glm::mat4(1.0f);
	M = glm::scale(M, vec3(config::scale, config::scale, 0.0f));
	float scalex = pos.x - config::scale / 2;
	float scaley = pos.y - config::scale / 2;
	M = glm::translate(M, vec3(scalex / config::scale, scaley / config::scale, 0.0f));*/
}

void pacman::changePosition()
{
	if (config::c)
	{
		pos.direction = config::c;
		config::c = NULL;
	}

	switch (pos.direction)
	{
	case 'u':
	{
		
		pos.y += speed;
		M = glm::mat4(1.0f);
		M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
		break;
	}
	case 'd':
	{
		pos.y-=speed;
		M = glm::mat4(1.0f);
		M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
		break;
	}
	case 'r':
	{
		pos.x+=speed;
		M = glm::mat4(1.0f);
		M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
		break;
	}
	case 'l':
	{
		pos.x-=speed;
		M = glm::mat4(1.0f);
		M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
		break;
	}
	default: 
		break;
	}
	
}