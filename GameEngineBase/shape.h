#ifndef _SHAPE_H
#define _SHAPE_H

#include "Vector3D.h"

class Shape
{
public:
	Shape(){};
	~Shape(){};

	Vector3D location;
	Vector3D velocity;
	Vector3D normalVec;
};



#endif