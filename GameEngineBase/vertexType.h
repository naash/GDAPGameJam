#ifndef _VERTEX_TYPE_CH
#define _VERTEX_TYPE_CH

#include <vector>

struct CVertex_fXYZW
{
	CVertex_fXYZW() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}; 
	float x, y, z, w;
};


struct vertexInfo
{
	float position[4];
	float normal[4];
	float texture[4];
};

struct softBodyAttribs
{
	float springConst;
	float indexOffset;
	std::vector<int> fixedNodes;
};
#endif