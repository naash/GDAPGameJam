#include "boundingBox.h"

#include <iostream>

BoundingBox::BoundingBox()
{

}

void BoundingBox::setminX(float value)
{
	b_minX = value;
}
void BoundingBox::setmaxX(float value)
{
	b_maxX = value;
}
void BoundingBox::setminY(float value)
{
	b_minY = value;
}
void BoundingBox::setmaxY(float value)
{
	b_maxY = value;
}
void BoundingBox::setminZ(float value)
{
	b_minZ = value;
}
void BoundingBox::setmaxZ(float value)
{
	b_maxZ = value;
}

BoundingBox::BoundingBox(float minX, float maxX, float minY, float maxY ,float minZ,float maxZ)
{
	b_minX = minX;
    b_maxX = maxX;
	b_minY = minY;
	b_maxY = maxY;
    b_minZ = minZ;
	b_maxZ = maxZ;

	centerX = (b_minX + b_maxX) / 2;
	centerY = (b_minY + b_maxY) / 2;
	centerZ = (b_minZ + b_maxZ) / 2;
	containsTriangles = false;
}

void BoundingBox::setData(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float min_id, float max_id)
{
	b_minX = minX;
	b_maxX = maxX;
	b_minY = minY;
	b_maxY = maxY;
	b_minZ = minZ;
	b_maxZ = maxZ;

	centerX = (b_minX + b_maxX) / 2;
	centerY = (b_minY + b_maxY) / 2;
	centerZ = (b_minZ + b_maxZ) / 2;

	this->id = min_id;
	containsTriangles = false;

	minPt = Vector3D(b_minX, b_minY, b_minZ);
	maxPt = Vector3D(b_maxX, b_maxY, b_maxZ);
	//std::cout << b_minX << " " << b_maxX << " y " << b_minY << " " << b_maxY << " z " << b_minZ << " " << b_maxZ << std::endl;
	//std::cout << "centerX " << centerX << " cent Y " << centerY << " cent Z " << centerZ << std::endl;
}

BoundingBox::~BoundingBox()
{

}

bool BoundingBox::containsVertex(Vector3D &vertex ,  Vector3D &offset )
{
	if(((b_minX + offset.x) < vertex.x) && (vertex.x < (b_maxX + offset.x)) && 
	   ((b_minY + offset.y) < vertex.y) && (vertex.y < (b_maxY + offset.y)) &&  
	   ((b_minZ + offset.z) < vertex.z) && (vertex.z < (b_maxZ + offset.z)) )
	    return true ;
	else 
		return false;
}

void BoundingBox::addTriangle(PLYELEMENT triangle)
{
	b_elements.push_back(triangle);
	
	containsTriangles = true;
}

bool BoundingBox::isEmpty()
{
	if(containsTriangles)
	{
		return false;
	}
	else
	{
		return true;
	}
}


Vector3D BoundingBox::getBBcenter()
{
	Vector3D val;
	val.x = centerX;
	val.y= centerY;
	val.z = centerZ;

	return val;

}

float BoundingBox::getminX()
{

	return b_minX;

}
float BoundingBox::getmaxX()
{

	return b_maxX;

}
float BoundingBox::getminY()
{

	return b_minY;

}
float BoundingBox::getmaxY()
{

	return b_maxY;

}
float BoundingBox::getminZ()
{

	return b_minZ;

}
float BoundingBox::getmaxZ()
{

	return b_maxZ;

}

	void BoundingBox::scaleBounds(float scale)
	{
	b_minX = b_minX * scale;
	b_maxX =  b_maxX * scale;
	b_minY = b_minY * scale;
	b_maxY = b_maxY * scale;
	b_minZ =  b_minZ * scale;
	b_maxZ = b_maxZ * scale;

	centerX = (b_minX + b_maxX) / 2;
	centerY = (b_minY + b_maxY) / 2;
	centerZ = (b_minZ + b_maxZ) / 2;
	containsTriangles = false;
	std::cout << b_minX << " " << b_maxX << " y " << b_minY << " " << b_maxY << " z " << b_minZ << " " << b_maxZ << std::endl;
	std::cout << "centerX " << centerX << " cent Y " << centerY << " cent Z " << centerZ << std::endl;
	
	
	}


	std::vector<PLYELEMENT> BoundingBox::getTriangles()
	{
	
	
		return b_elements;
	}


	void BoundingBox::computeAvgPoint(std::vector<PLYVERTEX> &list)
	{
		Vector3D centPoint;

		for(int i = 0 ; i < b_elements.size() ; i++)
		{
		 Vector3D  tri1V1 = list[b_elements[i].vertex_1].pos  ;//mesh1Vertices[mesh1Indices[(i*3)+0]].pos;
		Vector3D  tri1V2 = list[b_elements[i].vertex_2].pos  ;// mesh1Vertices[mesh1Indices[(i*3)+1]].pos;
		Vector3D   tri1V3 = list[b_elements[i].vertex_3].pos  ;


		centPoint += (tri1V1 + tri1V2 + tri1V3) /3 ;
		
		
		
		}
	
		
		this->centrePt = centPoint/ b_elements.size();

	//	std::cout<<"Centre point "<<this->centrePt.x<<" "<<this->centrePt.y<<" "<<this->centrePt.z<<std::endl;
	}


	Vector3D BoundingBox::getCenterPoint()
	{
	
		return centrePt;
	
	
	}


	Vector3D BoundingBox::getMixVertex()
	{
		return minPt;
	
	
	}
	Vector3D BoundingBox::getMaxVertex()
	{
	
		return maxPt;
	
	}