#include "pacman.h"



pacman::pacman()
{
	//jupi ja jej

}

pacman::pacman(int vertex)
{
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	vertexCount = vertex;
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