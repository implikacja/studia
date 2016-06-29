#ifndef POINT_H
#define POINT_H
class point
{
public:
	float x;
	float y;
	float z;
	int intX;
	int intY;
	char direction;
	float distance(point a);
	point();
	~point();
};

#endif