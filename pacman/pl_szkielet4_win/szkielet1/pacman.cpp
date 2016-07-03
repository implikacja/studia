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
			if (pos.x > cMap->h / 2)pos.x = -cMap->h / 2;
			if (cMap->m[j][i] == 'p')
			{
				pos.intX = j;
				pos.intY = i;
				flag = 1;
				break;
			}

			pos.x += config::width;
		}
		if (flag) break;
		pos.y -= config::width;
	}
	pos.z = 0;
	vertexCount = vertex;
	M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
	pos.direction = 'u';
	width = 1;
	height = 1;
	lastDir = 'u';
}

pacman::~pacman()
{
}

void pacman::nextFrame()
{
}

void pacman::changePosition(map *cMap, int &c)
{
	if (config::c)
	{
		pos.direction = config::c;
		config::c = NULL;
	}
	if (!collisionCheck(cMap))
	{
		switch (pos.direction)
		{
		case 'u':
		{
			pos.y += config::width;
			pos.intY--;
			if (cMap->m[pos.intX][pos.intY] == 'm')
			{
				c--;
				cMap->m[pos.intX][pos.intY] = 'n';
				if (!c) config::end = 1;

			}
			M = glm::mat4(1.0f);
			M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
			lastDir = 'u';
			break;
		}
		case 'd':
		{
			pos.y -= config::width;
			pos.intY++;
			if (cMap->m[pos.intX][pos.intY] == 'm')
			{
				c--;
				cMap->m[pos.intX][pos.intY] = 'n';
				if (!c) config::end = 1;

			}
			M = glm::mat4(1.0f);
			M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
			lastDir = 'd';
			break;
		}
		case 'r':
		{
			pos.x += config::width;
			pos.intX++;
			if (cMap->m[pos.intX][pos.intY] == 'm')
			{
				c--;
				cMap->m[pos.intX][pos.intY] = 'n';
				if (!c) config::end = 1;

			}
			M = glm::mat4(1.0f);
			M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
			lastDir = 'r';
			break;
		}
		case 'l':
		{
			pos.x -= config::width;
			pos.intX--;
			if (cMap->m[pos.intX][pos.intY] == 'm')
			{
				c--;
				cMap->m[pos.intX][pos.intY] = 'n';
				if (!c) config::end = 1;

			}
			M = glm::mat4(1.0f);
			M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
			lastDir = 'l';
			break;
		}
		default:
			break;
		}
	}
}


bool pacman::collisionCheck(map *cMap)
{
	int flag = 0;
	if (lastDir != pos.direction)
	{
		if (pos.intY>-1 && cMap->m[pos.intX][pos.intY - 1] == 'w' && lastDir == 'u') flag = 1;

		if (pos.intY<cMap->h && cMap->m[pos.intX][pos.intY + 1] == 'w' && lastDir == 'd') flag = 1;

		if (pos.intX>-1 && cMap->m[pos.intX - 1][pos.intY] == 'w' && lastDir == 'l') flag = 1;

		if (pos.intX<cMap->h && cMap->m[pos.intX + 1][pos.intY] == 'w' && lastDir == 'r') flag = 1;

	}


	if (pos.intY>-1 && cMap->m[pos.intX][pos.intY - 1] == 'w' && pos.direction == 'u')
	{
		if (!flag && lastDir!=pos.direction)
		{
			pos.direction = lastDir;
			return false;
		}
		return true;
	}else if (pos.intY<cMap->h && cMap->m[pos.intX][pos.intY + 1] == 'w' && pos.direction == 'd')
	{
		if (!flag&& lastDir != pos.direction)
		{
			pos.direction = lastDir;
			return false;
		}
		return true;
	}
	else if (pos.intX>-1 && cMap->m[pos.intX - 1][pos.intY] == 'w' && pos.direction == 'l')
	{
		if (!flag&& lastDir != pos.direction)
		{
			pos.direction = lastDir;
			return false;
		}
		return true;
	}
	else if (pos.intX<cMap->h && cMap->m[pos.intX + 1][pos.intY] == 'w' && pos.direction == 'r')
	{
		if (!flag && lastDir != pos.direction)
		{
			pos.direction = lastDir;
			return false;
		}
		return true;
	}
	return false;
}