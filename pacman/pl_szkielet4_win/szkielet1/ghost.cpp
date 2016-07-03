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
				break;
			}
			else if (cMap->m[j][i] == 'b' && n == 2)
			{
				pos.intX = j;
				pos.intY = i;
				flag = 1;
				break;
			}
			else if (cMap->m[j][i] == 'c' && n == 3)
			{
				pos.intX = j;
				pos.intY = i;
				flag = 1;
				break;
			}
			else if (cMap->m[j][i] == 'd' && n == 4)
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
	width = 1;
	height = 1;
	road.clear();
}

ghost::~ghost()
{
}

void ghost::gotoXY(int x, int y, map *cMap)
{
	vector <pair<int, int>>A;
	int nr = 0;
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
	m[pos.intX][pos.intY] = nr;

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
	int i = y;
	int j = x;
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
	if (nr == 1)
	{
		if (road.empty()) gotoXY(12, 12, cMap);

	}
	else if (nr == 2)
	{
		if (road.empty()) gotoXY(12, 12, cMap);

	}
	else if (nr == 3)
	{
		if (road.empty()) gotoXY(12, 12, cMap);
	}
	else if (nr == 4)
	{
		if (road.empty()) gotoXY(12, 12, cMap);
	}

	if (road[0].first < pos.intX)pos.direction = 'l';
	if (road[0].first > pos.intX)pos.direction = 'r';
	if (road[0].second > pos.intY)pos.direction = 'd';
	if (road[0].second < pos.intY)pos.direction = 'u';
    if(!road.empty())road.erase(road.begin());

	switch (pos.direction)
	{
	case 'u':
	{
		pos.y += config::width;
		pos.intY--;
		M = glm::mat4(1.0f);
		M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
		break;
	}
	case 'd':
	{
		pos.y -= config::width;
		pos.intY++;
		M = glm::mat4(1.0f);
		M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
		break;
	}
	case 'r':
	{
		pos.x += config::width;
		pos.intX++;
		M = glm::mat4(1.0f);
		M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
		break;
	}
	case 'l':
	{
		pos.x -= config::width;
		pos.intX--;
		M = glm::mat4(1.0f);
		M = glm::translate(M, vec3(pos.x, pos.y, pos.z));
		break;
	}
	default:
		break;
	}
}