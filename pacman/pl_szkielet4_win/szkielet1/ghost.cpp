#include "ghost.h"



ghost::ghost()
{
	
}

ghost::ghost(int vertex, map *cMap, int n)
{
	nr = n;
	pos.x = -cMap->h / 2;
	pos.y = cMap->h / 2;
	bool flag = 0;
	for (int i = 0; i < cMap->h; i++)
	{
		for (int j = 0; j < cMap->h; j++)
		{
			if (pos.x > cMap->h / 2)pos.x = -cMap->h / 2;
			if (cMap->m[j][i] == 'a' && n == 1)
			{
				pos.intX = j;
				pos.intY = i;
				flag = 1;
				ghostPos[0][0] = pos.intX;
				ghostPos[0][1] = pos.intY;
				break;
			}
			else if (cMap->m[j][i] == 'b' && n == 2)
			{
				pos.intX = j;
				pos.intY = i;
				flag = 1;
				ghostPos[1][0] = pos.intX;
				ghostPos[1][1] = pos.intY;
				break;
			}
			else if (cMap->m[j][i] == 'c' && n == 3)
			{
				pos.intX = j;
				pos.intY = i;
				flag = 1;
				ghostPos[2][0] = pos.intX;
				ghostPos[2][1] = pos.intY;
				break;
			}
			else if (cMap->m[j][i] == 'd' && n == 4)
			{
				pos.intX = j;
				pos.intY = i;
				flag = 1;
				ghostPos[3][0] = pos.intX;
				ghostPos[3][1] = pos.intY;
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
	pM = glm::mat4(0.0f);
	width = 1;
	height = 1;
	road.clear();
	start.x = pos.x;
	start.y = pos.y;
	start.intY = pos.intY;
	start.intX = pos.intX;

	for (int i = 0; i < cMap->h; i++)
	{
		for (int j = 0; j < cMap->w; j++)
		{
			if (cMap->m[j][i] != 'w')
				ghost::vertex.push_back(make_pair(j, i));
		}
	}
	t_max = GHOST_SPEED;
	shine = GHOST_SHINE;
}

ghost::~ghost()
{
}

void ghost::gotoXY(int x, int y, map *cMap)
{
	vector <pair<int, int>>A;
	int n = 0;
	pair <int, int> v;
	bool flag = 0;
	int **m = new int*[cMap->w];
	for (int i = 0; i < cMap->w; i++) m[i] = new int[cMap->h];
	for (int i = 0; i < cMap->h; i++)
	{
		for (int j = 0; j < cMap->h; j++)
		{
			m[j][i] = 89;

		}

	}

	A.push_back(make_pair(pos.intX, pos.intY));
	m[pos.intX][pos.intY] = n;
	while (!A.empty())      
	{
		v = A.front();     
		A.erase(A.begin());


		if (m[v.first - 1][v.second] == 89 && cMap->m[v.first - 1][v.second] != 'w')
		{
			A.push_back({v.first-1,v.second});
			m[v.first-1][v.second] = m[v.first][v.second]+1;
		}
		if (m[v.first + 1][v.second] == 89 && cMap->m[v.first + 1][v.second] != 'w')
		{
			A.push_back({ v.first + 1,v.second });
			m[v.first + 1][v.second] = m[v.first][v.second] + 1;
		}
		if (m[v.first][v.second - 1] == 89 && cMap->m[v.first][v.second - 1] != 'w')
		{
			A.push_back({ v.first,v.second - 1 });
			m[v.first][v.second - 1] = m[v.first][v.second] + 1;
		}
		if (m[v.first][v.second + 1] == 89 && cMap->m[v.first][v.second + 1] != 'w')
		{
			A.push_back({ v.first,v.second + 1 });
			m[v.first][v.second + 1] = m[v.first][v.second] + 1;
		}
		if (m[x][y] != 89)break;
	}
	int i = x;
	int j =y;
	while (m[i][j] != 0)
	{
		road.insert(road.begin(), make_pair(i, j));
		if (m[i - 1][j] < m[i][j])i--;
		else if (m[i + 1][j] < m[i][j])i++;
		else if (m[i][j-1] < m[i][j])j--;
		else if (m[i][j+1] < m[i][j])j++;
	}
}

void ghost::changePosition(map *cMap, int &c)
{
	if (item::dead == 1 && item::nextDead != 0)
	{
		c--;
		if (!c)
		{
			config::end = -1;
			return;
		}
	}
	if (nextDead==nr)
	{

		pos.x = start.x;
		pos.y = start.y;
		pos.intX = start.intX;
		pos.intY = start.intY;
		nextDead = 0;
		M = glm::mat4(1.0f);
		M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
		ghostPos[nr - 1][0] = pos.intX;
		ghostPos[nr - 1][1] = pos.intY;
	}
	else
	{
		if (item::dead)
		{
		}
		srand(time(0));
		if (nr == 1)
		{
			if (road.empty() && pos.intX == start.intX && pos.intY == start.intY)
			{
				gotoXY(23, 23, cMap);
			}
			else if (road.empty()) gotoXY(start.intX, start.intY, cMap);

		}
		else if (nr == 2)
		{
			if (road.empty())
			{
				int r = rand() % vertex.size();

				int x = vertex[r].first;
				int y = vertex[r].second;
				gotoXY(x, y, cMap);
			}
		}
		else if (nr == 3)
		{
			if (road.empty())
			{
				int r = rand() % vertex.size();
				r = (r + rand() % 9) % vertex.size();

				int x = vertex[r].first;
				int y = vertex[r].second;
				gotoXY(x, y, cMap);
			}
		}
		else if (nr == 4)
		{
			for (int i = 0; i < cMap->h; i++)
			{
				for (int j = 0; j < cMap->w; j++)
				{
					if (cMap->m[j][i] == 'p')
					{
						road.clear();
						gotoXY(j, i, cMap);
					}
				}
			}
		}

		if (road[0].first < pos.intX)pos.direction = 'l';
		if (road[0].first > pos.intX)pos.direction = 'r';
		if (road[0].second > pos.intY)pos.direction = 'd';
		if (road[0].second < pos.intY)pos.direction = 'u';
		if (!road.empty())road.erase(road.begin());


		switch (pos.direction)
		{
		case 'u':
		{
			pos.y += config::width;
			pos.intY--;
			if (cMap->m[pos.intX][pos.intY] == 'p')
			{
				item::dead = 1;
				c--;
				if (!c)
				{
					config::end = -1;
					return;
				}
				pos.x = start.x;
				pos.y = start.y;
				pos.intX = start.intX;
				pos.intY = start.intY;

			}
			M = glm::mat4(1.0f);
			M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
			ghostPos[nr - 1][0] = pos.intX;
			ghostPos[nr - 1][1] = pos.intY;


			break;
		}
		case 'd':
		{
			pos.y -= config::width;
			pos.intY++;
			if (cMap->m[pos.intX][pos.intY] == 'p')
			{
				item::dead = 1;
				c--;
				if (!c)
				{
					config::end = -1;
					return;
				}
				pos.x = start.x;
				pos.y = start.y;
				pos.intX = start.intX;
				pos.intY = start.intY;
			}
			M = glm::mat4(1.0f);
			M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
			ghostPos[nr - 1][0] = pos.intX;
			ghostPos[nr - 1][1] = pos.intY;
			break;
		}

		case 'r':
		{
			pos.x += config::width;
			pos.intX++;
			if (cMap->m[pos.intX][pos.intY] == 'p')
			{
				item::dead = 1;
				c--;
				if (!c)
				{
					config::end = -1;
					return;
				}
				pos.x = start.x;
				pos.y = start.y;
				pos.intX = start.intX;
				pos.intY = start.intY;
			}
			ghostPos[nr - 1][0] = pos.intX;
			ghostPos[nr - 1][1] = pos.intY;
			M = glm::mat4(1.0f);
			M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
			break;
		}
		case 'l':
		{
			pos.x -= config::width;
			pos.intX--;
			if (cMap->m[pos.intX][pos.intY] == 'p')
			{
				item::dead = 1;
				c--;
				if (!c)
				{
					config::end = -1;
					return;
				}
				pos.x = start.x;
				pos.y = start.y;
				pos.intX = start.intX;
				pos.intY = start.intY;
			}
			ghostPos[nr - 1][0] = pos.intX;
			ghostPos[nr - 1][1] = pos.intY;
			M = glm::mat4(1.0f);
			M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
			break;
		}
		default:
			break;
		}
	
	}
	
}