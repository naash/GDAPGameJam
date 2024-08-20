#ifndef _SPHERE_GO
#define _SPHERE_GO

#include "gameObject.h"

class SphereObj : public GameObject
{
public:
SphereObj();
~SphereObj();

float getRadius();
void setRadius(float value);
private:
	float radius;
};


#endif