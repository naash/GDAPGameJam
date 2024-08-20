#include "springs.h"

sSpring::sSpring()
{

}

	sSpring::sSpring( sNode* nodeA, sNode* nodeB, float length )
	{
		NodeA = nodeA;
		NodeB = nodeB;
		RestLength = length;
		Length = length;
	}

	sSpring::~sSpring()
	{
		delete NodeA;
		delete NodeB;
	}


	sNode::sNode( unsigned int idxVert, float x, float y, float z )
	{
		IdxVert = idxVert;
		FixedPosition = false;
		Position = Vector3D(x,y,z);
		PreviousPosition = Vector3D(x,y,z);
	}

	sNode::~sNode()
	{
		std::map<unsigned int, sSpring*>::iterator it = Springs.begin();
			while(it != Springs.end() )
			{
				delete (it->second);
				it ++;
			};

		Springs.clear();
	}
