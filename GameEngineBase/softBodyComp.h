#ifndef _SOFTBODY_PHY
#define _SOFTBODY_PHY

#include "basePhyComp.h"
#include "springs.h"
#include <vector>
#include "plyInfo.h"
#include "vertexType.h"

class SoftBodyPhyComp : public BasePhyComp
{
public:
	SoftBodyPhyComp();
	~SoftBodyPhyComp();

	void UpdatePhysics(float deltaTime);
	void GetPosition(unsigned int idx, CVertex_fXYZW &floatXYZ);
	void SetNodeFixed(unsigned int idx, bool value);
	void SetVertices(const std::vector<PLYVERTEX>& vertices, float radius);
	void SetSpringConst(float p_mk);
	void ComputeSprings(const std::vector<PLYELEMENT>& indices, float offset);
	void SetSpringsFromTriangulatedIndices(const std::vector<unsigned int>& indices);
	void AddSpring(unsigned int idxA, unsigned int idxB);
	std::vector<sNode*> GetNodeList();
	 void CheckForCollision();
private:

	std::vector<sNode*> mNodes;
	std::vector<sSpring*> mSprings;


	float mTime;
	float mRadius;
	Vector3D mGravity;
	float mDamping; // spring damping
	float mK;// spring constant
	float mMass;// mass per vertex
	Vector3D mWind;// wind vector


	void CalculateSpringForces();
	void SetSpringLengths();

};

#endif