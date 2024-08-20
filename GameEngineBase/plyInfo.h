#ifndef _PLYINFO_CH
#define _PLYINFO_CH

#include "Vector3D.h"

// This structure holds the vertex information 
// as listed in the bunny file
struct PLYVERTEX
{
	// **** ADDED THIS ****
	PLYVERTEX(): nx(0.0f), ny(0.0f), nz(0.0f), 
				 tex0u(0.0f), tex0v(0.0f), tex1u(0.0f), tex1v(0.0f),
				 red(0), green(0), blue(0) {}
	Vector3D pos; 
	//float x, y, z;
	float nx, ny, nz;
	float tex0u, tex0v;
	float tex1u, tex1v;
	// *********************
	float red, green, blue;
};

// This structure holds the elements, which 
// refer to the vertex indicies
struct PLYELEMENT
{
	// **** ADDED THIS ****
	PLYELEMENT(): vertex_1(0), vertex_2(0), vertex_3(0) {}
	int vertex_1;
	int vertex_2;
	int vertex_3;
};


#endif