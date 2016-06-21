#pragma once
class point
{
public:
	float x;
	float y;
	float z;
	char direction;
	float distance(point a);
	point();
	~point();
};

