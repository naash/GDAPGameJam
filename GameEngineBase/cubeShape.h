#ifndef _CUBE_SH
#define _CUBE_SH

#include "shape.h"

class Cube : public Shape
{
public:
	Cube(){};
	~Cube(){};

	Vector3D min;
	Vector3D max;

};

#endif