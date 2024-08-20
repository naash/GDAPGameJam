#ifndef _COLLIDE_H
#define _COLLIDE_H


#include "Physics.h"
#include "modelData.h"
#include <vector>

#include "sphereShape.h"
#include "cubeShape.h"

class Collision
{
public:
	Collision();
	~Collision();


//void CollisionCheckForSphere(std::vector< GameObject* > vec_pGameObjects, int playerIndex);
//
//// Called to check Sphere collisions
//void SphereToEnvCollision(GameObject* sphere , GameObject* envObj, std::vector<Physics::Point> &listOfClosestPt);
//void SphereToSphereCollision(GameObject* sphere1 , GameObject* sphere2, std::vector<Physics::Point> &listOfClosestPt);
////.......................
//
////.......For physics 2 ................................
//void CollisionCheckForSub(std::vector< GameObject* > &vec_pGameObjects, int playerIndex, bool &collision,  Vector3D &origin);
//void BoundingToBoundingBox(GameObject* &object1, GameObject* &object2,  bool &collision ,  Vector3D &origin);
//void SphereToBoundingBox(GameObject* sphere, GameObject* env, std::vector<Physics::Point> &listOfClosestPt);
//bool AABBtoAABB(BoundingBox& tBox1, Vector3D &offset, BoundingBox& tBox2);
//
//
//bool TriTriCollisionDetect(PLYELEMENT &mesh1, GameObject* &mesh1ObjSpace, PLYELEMENT &mesh2, GameObject* &mesh2ObjSpace);
//bool TriBoundingBoxCollisionDetect(PLYELEMENT &mesh1, GameObject* &mesh1ObjSpace, std::vector<PLYVERTEX> &vertInfo1 , BoundingBox &tBox2, bool &vert1, bool &vert2, bool &vert3, Vector3D &offset);
//
////Give Paramters as ... 1 . Triangle collided , 2. Vertex info , 3. object 
//void CollisionResponeClamping(PLYELEMENT &mesh2,std::vector<PLYVERTEX> &vertInfo2, GameObject* &mesh1ObjSpace);

//.........Second component will be translated.......
static bool SphereToSphereCollision(Sphere &sphere1 , Sphere &sphere2);
static bool CubeToSphereCollision(Cube &cube, Sphere &sphere);
static bool MeshToSphereCollision(Shape &shape, Sphere &sphere, ModelData* shapeModel, Vector3D &pt);
static bool CubeToCubeCollision(Cube &cube1, Cube &cube2);

static bool SphereToSphereCollisionVelTransfer(Sphere& sphere1 , Sphere &sphere2, Vector3D &pt);
static void VelocityToClampSphere(Vector3D &a, Vector3D &b, Vector3D &c,Sphere &sphere, Vector3D &velocity);
private:
	std::vector<int> prevTriColl;
};


#endif