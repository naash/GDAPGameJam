#ifndef _SPRINGS_H
#define _SPRINGS_H

#include <map>
#include "Vector3D.h"

	class sSpring;
	class sNode
	{
	public:
		sNode(unsigned int idxVert, float x, float y, float z);
		~sNode();
		
		Vector3D Position;
		Vector3D PreviousPosition;
		Vector3D Velocity;
		Vector3D Acceleration;
		Vector3D SpringForce;
		float radius;
		bool FixedPosition;
		bool collided;
		unsigned int IdxVert;
		std::map<unsigned int, sSpring*> Springs;
	};


	class sSpring
	{
	public:
		sSpring();
		sSpring(sNode* , sNode* , float);
		~sSpring();
		sNode* NodeA;
		sNode* NodeB;
		float RestLength;
		float Length;
	};

#endif