#include "map.h"


map::map()
{
	ifstream file;
	file.open("map.txt");
	if (file.good())
	{
		file >> w >> h;
		m = new char*[w];
		for (int i = 0; i < w; i++) m[i] = new char[h];

		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				file >> m[j][i];

		file.close();

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
				printf("%c ",m[j][i]);
			printf("\n");
		}
	}
	else
	{
		fprintf(stderr, "Nie mo¿na otworzyæ pliku z map¹.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}



}

map::~map()
{
	for (int i = 0; i < w; i++) delete[] m[i];
	delete[] m;
}
