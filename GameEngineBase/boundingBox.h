#ifndef _Bounding_Box_h
#define _Bounding_Box_h

#include "plyInfo.h"
#include <vector>
#include "Vector3D.h"

class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(float minX, float maxX, float minY, float maxY ,float minZ,float maxZ);
	~BoundingBox();
	void setData(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float min_id, float max_id);
	std::vector<PLYELEMENT> BoundingBox::getTriangles();
	
	bool containsVertex(Vector3D &vertex, Vector3D &offset );
	void addTriangle(PLYELEMENT triangle);
	void computeAvgPoint(std::vector<PLYVERTEX> &list);
	Vector3D getBBcenter();
	bool isEmpty();
	void scaleBounds(float scale);

	Vector3D getMixVertex();
	Vector3D getMaxVertex();

	float BoundingBox::getminX();
	float BoundingBox::getmaxX(); 
	float BoundingBox::getminY();
	float BoundingBox::getmaxY();
	float BoundingBox::getminZ();
	float BoundingBox::getmaxZ();

	void BoundingBox::setminX(float value);
	void BoundingBox::setmaxX(float value);
	void BoundingBox::setminY(float value);
	void BoundingBox::setmaxY(float value);
	void BoundingBox::setminZ(float value);
	void BoundingBox::setmaxZ(float value);

	Vector3D getCenterPoint();
private:
	float b_minX, b_maxX;
	float b_minY, b_maxY;
	float b_minZ, b_maxZ;
	float id;
	std::vector<PLYELEMENT> b_elements;
	bool containsTriangles;
	Vector3D minPt ;
	Vector3D maxPt; 
	Vector3D centrePt ;
	float centerX, centerY, centerZ;



};

#endif