#include "collisionTest.h"

#include "sphereShape.h"
#include <math.h>
#include <iostream>
Collision::Collision()
{

}

Collision::~Collision()
{

}


//
//
//void  Collision::SphereToEnvCollision(GameObject* sphere , GameObject* envObj ,std::vector<Physics::Point> &listOfClosestPt)
//{
////Physics::Point playerPos;
////playerPos;// = sphere->getPosition();
////
////Sphere* s = (Sphere*)sphere;
////    float distance = 99.0f; 
////float radius = s->getRadius();
////
////
////std::vector<PLYVERTEX> m_verticies = envObj->getVerticiesForSimulation();
////std::vector<PLYELEMENT> m_elements = envObj->getElements();
////std::vector<Physics::Point> closestPointsofObj ;
////Physics::Point closestPoint ;
////	
////for(int i=0; i< m_elements.size(); i++ )
////	{
////
////		Physics::Point a(m_verticies[m_elements[i].vertex_1].pos.x,
////			             m_verticies[m_elements[i].vertex_1].pos.y,
////						 m_verticies[m_elements[i].vertex_1].pos.z) ;
////
////		Physics::Point b(m_verticies[m_elements[i].vertex_2].pos.x,
////			             m_verticies[m_elements[i].vertex_2].pos.y,
////						 m_verticies[m_elements[i].vertex_2].pos.z) ;
////
////		Physics::Point c(m_verticies[m_elements[i].vertex_3].pos.x,
////			             m_verticies[m_elements[i].vertex_3].pos.y,
////						 m_verticies[m_elements[i].vertex_3].pos.z) ;
////
////		
////		bool bIsInsideFace = false;
////	
////
////	   Physics::Point newclosestPoint = Physics::ClosestPtPointTriangle(playerPos, a, b, c, bIsInsideFace );
////	   float newDist = Physics::Distance(newclosestPoint,playerPos);
////	   
////	   if(newDist < distance)
////		{
////			closestPoint = newclosestPoint;
////		    distance = newDist;
////
////		
////			if(distance <= radius)
////			{
////				closestPointsofObj.push_back(newclosestPoint);
////			}
////		  
////	  
////	
////		}
////			 
////	}
////
////			//Calculate actual closest dist of that object 
////	if( closestPointsofObj.size() > 0)
////	{
////		Physics::Point sumObj(0.0f,0.0f,0.0f);
////		for(int i = 0 ; i < closestPointsofObj.size(); i++)
////		{
////			sumObj += closestPointsofObj[i];
////		}
////		
////		sumObj /= closestPointsofObj.size();
////	
////		listOfClosestPt.push_back(sumObj);
////	}
//
//}
//void Collision::SphereToSphereCollision(GameObject* sphere1 , GameObject* sphere2,  std::vector<Physics::Point> &listOfClosestPt)
//{
//	//// Proximity test for sphere to sphere
//	//Physics::Sphere a ;
//	//a.c = sphere1->getPosition();
//	//a.vel = sphere1->getVelocity();
//	//sphere1->radius = ((Sphere*)sphere1)->getRadius() ;
//
//	//Physics::Sphere b ; 
//	//b.c = sphere2->getPosition();
//	//b.r = ((Sphere*)sphere2)->getRadius();
//	//b.vel = sphere2->getVelocity(); 
//	//
//	//Physics::Point closestPt;
//	//Vector3D newVel ; 
//	//				
//	//if(Physics::ClosestPtSphereSphere( a,b, closestPt))
//	//{
//	//	listOfClosestPt.push_back(closestPt);
//
//	//	//Calculate change in velocity
//	//	Vector3D newVelocityA ; 
//	//    Vector3D newVelocityB ; 
//	//	newVelocityA.x = ((a.vel.x * (a.r - b.r)) + (2 * b.r * b.vel.x)) / (a.r + b.r);
//	//	newVelocityA.y = ((a.vel.y * (a.r - b.r)) + (2 * b.r *b.vel.y)) / (a.r + b.r);
//	//	newVelocityA.z = ((a.vel.z * (a.r - b.r)) + (2 * b.r * b.vel.z)) / (a.r + b.r);
//	//				  
//	//	sphere1->setVelocity(newVelocityA);
//
//	//	newVelocityB.x = ((b.vel.x * (a.r - b.r)) + (2 * b.r * a.vel.x )) / (a.r + b.r);
//	//	newVelocityB.y = ((b.vel.y  * (a.r - b.r)) + (2 * b.r *a.vel.y)) / (a.r + b.r);
//	//	newVelocityB.z = ((b.vel.z  * (a.r - b.r)) + (2 * b.r * a.vel.z)) / (a.r + b.r);
//
//	//
//	//	sphere2->setVelocity(newVelocityB);
//	//}
//		
//}
//
//void Collision::CollisionCheckForSphere(std::vector< GameObject* > vec_pGameObjects, int playerIndex)
//{
////	//check for collisions
////	Sphere* sphere = (Sphere*)vec_pGameObjects[playerIndex];
////
////	Vector3D playerPos;// = sphere->getPosition();
////	float radius = sphere->getRadius();
////
////	std::vector<Vector3D> closestPointsInEnv ; //It contains list of closest points of all objects
////	Physics::Point closestPoint ;
////	     
////	float distance = 99.0f; 
////
////	 
////	for(int j =0; j < vec_pGameObjects.size(); j++)
////	{
////		if(j == playerIndex)
////		{
////			continue;
////		}
////
////		if(vec_pGameObjects[j]->getName() != "SPHERE")
////		{
////			// Proximity test for sphere to other objects
////			//SphereToEnvCollision(vec_pGameObjects[playerIndex], vec_pGameObjects[j] , closestPointsInEnv);
////			//SphereToBoundingBox(vec_pGameObjects[playerIndex], vec_pGameObjects[j], closestPointsInEnv);
////			//BoundingToBoundingBox(vec_pGameObjects[playerIndex], vec_pGameObjects[j], closestPointsInEnv);
////
////		
////		}
////		else
////		{
////		    // Proximity test for sphere to sphere
////			SphereToSphereCollision(vec_pGameObjects[playerIndex], vec_pGameObjects[j] , closestPointsInEnv);
////		}
////				
////							
////	}
////
////	Physics::Point sumEnv(0.0f,0.0f,0.0f);
////
////	for(int i = 0 ; i < closestPointsInEnv.size(); i++)
////	{
////		sumEnv += closestPointsInEnv[i];
////	}
////	
////	sumEnv /= closestPointsInEnv.size();
////
////		//if distance is less than radius bind the ball
////	if(closestPointsInEnv.size() > 0 )
////	{
////		Physics::Point dist =  playerPos -sumEnv ;
////	    Vector3D::Normalize( dist.x, dist.y,dist.z);
////		
////		dist = dist * radius;
////		
////
////		Physics::Point distToTraverse = sumEnv + dist;
//////		vec_pGameObjects[playerIndex]->setPosition(distToTraverse);// newPoint;
////		
////		
////	}
////
////
//}
//
//void Collision::SphereToBoundingBox(GameObject* sphere, GameObject* env, std::vector<Physics::Point> &listOfClosestPt)
//{
//
//	//Physics::Point PlayerPos;
//	//PlayerPos=sphere->getPosition();
//
//
//	//Sphere* objsphere = (Sphere*)sphere;
//	//float dist = 99.0f;
//	//float radius = objsphere->getRadius();
//
//	//std::vector<BoundingBox> vecToCompare;
//	//vecToCompare = env->getBoundingBoxes();
//	//std::vector<Vector3D> BoundingBoxCollided;
//	//float boxsize=env->getModelData()->box_inc;
//	//
//	//
//	//for (int i = 0; i < vecToCompare.size(); i++)
//	//{
//	//	Vector3D center = vecToCompare[i].getBBcenter();
//	//	float newDist = Physics::Distance(center,PlayerPos );
//	//	
//
//	//	//std::cout << newDist << std::endl;
//	//		if (newDist <= radius+boxsize/2)
//	//		{
//	//			BoundingBoxCollided.push_back(center);
//	//		}
//
//
//
//	//	}
//	//
//	////Calculate actual closest dist of that object 
//	//if (BoundingBoxCollided.size() > 0)
//	//{
//	//	Physics::Point sumObj(0.0f, 0.0f, 0.0f);
//	//	for (int i = 0; i < BoundingBoxCollided.size(); i++)
//	//	{
//	//		sumObj += BoundingBoxCollided[i];
//	//		std::cout << "Box:" << i<<std::endl;
//	//	}
//
//	//	sumObj /= BoundingBoxCollided.size();
//
//	//	listOfClosestPt.push_back(sumObj);
//	//}
//
//	}
//
//void Collision::BoundingToBoundingBox(GameObject* &object1, GameObject* &object2,bool &collision,  Vector3D &origin)
//{
//	Vector3D collisionTri ;
//
//	////First object will be our sub 
//	//std::vector<BoundingBox> obj1VecToCompare;
//	//obj1VecToCompare = object1->getBoundingBoxes();
//
//	//Vector3D pos = object1->getPosition();
//
//	//int id = ModelData::generateID(pos.x, pos.y, pos.z);
//	////Second object will be terrain
//	//std::vector<BoundingBox> obj2VecToCompare  = object2->getBoundingBoxes();
//	////obj2VecToCompare = object2->getBoundingBoxesById(id);
//	//BoundingBox currentBox ;
//	// std::vector<PLYELEMENT> tri2 ;// obj2VecToCompare[j].getTriangles();
//	// std::vector<PLYELEMENT> tri1;
//	////Check in which bounding box does position currently lie 
//	//bool isInBox = true;
//
//	//if(isInBox)
//	//{
//	////std::vector<Vector3D> BoundingBoxCollided;
//
//	//std::vector<PLYVERTEX> vertInfo2 = object2->getVerticiesForSimulation();
//	//std::vector<PLYVERTEX> vertInfo1 = object1->getVerticiesForSimulation();
//	//bool collided = false;
//	//for (int i = 0; i < obj1VecToCompare.size(); i++)
//	//{
//	//	// tri1 = obj2VecToCompare[i].getTriangles();
//
//	//	if(!obj1VecToCompare[i].isEmpty()){
//	//	     for (int j = 0; j < obj2VecToCompare.size(); j++)
//	//	     {
//	//			
//
//	//		    if(!obj2VecToCompare[j].isEmpty())
//	//			{
//	//			      if (AABBtoAABB(obj1VecToCompare[i], pos, obj2VecToCompare[j]))
//	//			      {
//	//				   // std::vector<PLYELEMENT> tri1 = obj1VecToCompare[i].getTriangles();
//	//				     tri2 = obj2VecToCompare[j].getTriangles();
//	//					  // std::cout<<"Box  collision Box " <<i  << " with Box "<< j << std::endl;
//	//				   
//	//				   //Triangles of outer bounding box 
//	//				   for(int x = 0 ; x < tri2.size() ; x++)
//	//				   {
//	//					   bool vert1 = false;
//	//					   bool vert2 = false;
//	//					   bool vert3 = false;
//	//					  if(TriBoundingBoxCollisionDetect(tri2[x], object2,vertInfo2, obj1VecToCompare[i],vert1 , vert2, vert3,pos ))
//	//					  {
//
//	//						   CollisionResponeClamping(tri2[x], vertInfo2,object1);
//	//						    origin =  vertInfo2[tri2[x].vertex_1].pos;
//	//							std::printf("collision occured Triangle %i \n",x);
//	//							
//	//							
//	//							collision= true;
//	//						    break;
//	//							
//
// //
//	//					  }
//	//				
//	//				   }
//
//	//			     }
//	//		       }
//
//	//			if(collision)
//	//				break;
//	//	       }
//
//
//	//		 if(collision)
//	//				break;
//	//	}
//	//
//	//}
// // }
//	//
//}
//
//
//bool Collision::AABBtoAABB(BoundingBox& tBox1, Vector3D &offset, BoundingBox& tBox2)
//{
//
//	//Check if Box1's max is greater than Box2's min and Box1's min is less than Box2's max
//	return((tBox1.getmaxX() + offset.x) > tBox2.getminX() &&
//		   (tBox1.getminX() + offset.x) < tBox2.getmaxX() &&
//		   (tBox1.getmaxY() + offset.y) > tBox2.getminY() &&
//		   (tBox1.getminY() + offset.y) < tBox2.getmaxY() &&
//		   (tBox1.getmaxZ() + offset.z) > tBox2.getminZ() &&
//		   (tBox1.getminZ() + offset.z) < tBox2.getmaxZ());
//
//	//If not, it will return false
//
//}
//
//
//
////For triangle to triangle collision
//
//bool Collision::TriTriCollisionDetect(PLYELEMENT &mesh1, GameObject* &mesh1ObjSpace, PLYELEMENT &mesh2, GameObject* &mesh2ObjSpace)
//{
//	
//
//	//Detect Collision
//	//for(int i = 0; i < numMesh1Faces; i++)
//	//{
//		//Triangle's vertices V1, V2, V3
//	  Vector3D tri1V1;//= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	  Vector3D tri1V2; //= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	  Vector3D tri1V3; //= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	  std::vector<PLYVERTEX> vertInfo1 = mesh1ObjSpace->getVerticiesForSimulation();
//		//Get mesh1's triangle
//	    tri1V1 = vertInfo1[mesh1.vertex_1].pos  ;//mesh1Vertices[mesh1Indices[(i*3)+0]].pos;
//		tri1V2 = vertInfo1[mesh1.vertex_2].pos  ;// mesh1Vertices[mesh1Indices[(i*3)+1]].pos;
//		tri1V3 = vertInfo1[mesh1.vertex_3].pos  ;//mesh1Vertices[mesh1Indices[(i*3)+2]].pos;
//		
//		
//		//Find the normal using U, V coordinates
//		Vector3D U ;// = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		Vector3D V ;//= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		Vector3D faceNormal ;//= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		U = tri1V2 - tri1V1;
//		V = tri1V3 - tri1V1;
//
//		//Comput face normal using U, V
//		faceNormal = Vector3D::CrossProduct(U , V); //D3DXVec3Cross(&faceNormal, &U, &V);
//		Vector3D::Normalize(faceNormal.x , faceNormal.y, faceNormal.y);
//		//D3DXVec3Normalize(&faceNormal, &faceNormal);
//
//		//Calculate a point on the triangle
//		Vector3D triPoint = (tri1V1 + tri1V2 + tri1V3)/3;
//
//		//Get plane equation "Ax + By + Cz + D = 0" Variables
//		float tri1A = faceNormal.x;
//		float tri1B = faceNormal.y;
//		float tri1C = faceNormal.z;
//		float tri1D = (-tri1A*triPoint.x - tri1B*triPoint.y - tri1C*triPoint.z); 
//
//		//Now loop through second mesh's faces to check for collision
//		//for(int j = 0; j < numMesh2Faces; j++)
//		//{
//			//Triangle's vertices V1, V2, V3
//			Vector3D tri2V1 ;//= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			Vector3D tri2V2 ;//= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			Vector3D tri2V3 ;//= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			std::vector<PLYVERTEX> vertInfo2 = mesh2ObjSpace->getVerticiesForSimulation();
//			//Get mesh2's triangle
//			 tri2V1 = vertInfo2[mesh2.vertex_1].pos  ;//mesh1Vertices[mesh1Indices[(i*3)+0]].pos;
//	         tri2V2 = vertInfo2[mesh2.vertex_2].pos  ;// mesh1Vertices[mesh1Indices[(i*3)+1]].pos;
//		     tri2V3 = vertInfo2[mesh2.vertex_3].pos  ;//mesh1Vertices[mesh1Indices[(i*3)+2]].pos;
//			
//			//Transform triangles vertice's to second objects world space
//		
//
//			float ep1, ep2, t = 0.0f;
//			float planeIntersectX, planeIntersectY, planeIntersectZ = 0.0f;
//			Vector3D pointInPlane ;//= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//			Vector3D t2V[4]; //Triangle 2 vertices, array used for loop
//			t2V[0] = tri2V1;
//			t2V[1] = tri2V2;
//			t2V[2] = tri2V3;
//			t2V[3] = tri2V1;
//
//			for(int k = 0; k < 3; k++)
//			{
//				//Calculate where on the line, created from this trangles
//				//edge (eg. tri2V1, tri2V2), intersects with the plane
//				ep1 = (tri1A * t2V[k].x) + (tri1B * t2V[k].y) + (tri1C * t2V[k].z);
//				ep2 = (tri1A * t2V[k+1].x) + (tri1B * t2V[k+1].y) + (tri1C * t2V[k+1].z);
//
//				//Set t to -1 in case there is a divide-by-zero
//				t = -1;
//
//				//Make sure there are no divide-by-zeros
//				if(ep1 != ep2)
//					t = -(ep2 + tri1D)/(ep1 - ep2);
//
//				//If the lines intersection with the triangles plane was between the
//				//two vertices (tri2V1, tri2V2), calculate the point of intersection
//				if(t >= 0.0f && t <= 1.0f)
//				{
//					planeIntersectX = (t2V[k].x * t) + (t2V[k+1].x * (1 - t));
//					planeIntersectY = (t2V[k].y * t) + (t2V[k+1].y * (1 - t));
//					planeIntersectZ = (t2V[k].z * t) + (t2V[k+1].z * (1 - t));
//
//					pointInPlane = Vector3D(planeIntersectX, planeIntersectY, planeIntersectZ);
//
//					//Call function to check if point is in the triangle
//					if(Physics::TestPointTriangle(pointInPlane, tri1V1, tri1V2, tri1V3))
//					{
//						return true; //There was an intersection
//					}
//				}
//			}
//		//}
//	//}
//
//	return false; //There was no intersection
//}
//
//
//bool Collision::TriBoundingBoxCollisionDetect(PLYELEMENT &mesh1, GameObject* &mesh1ObjSpace,std::vector<PLYVERTEX> &vertInfo1, BoundingBox &tBox2, bool &vert1, bool &vert2, bool &vert3 , Vector3D &offset)
//{
//	//std::vector<PLYVERTEX> vertInfo1 = mesh1ObjSpace->getVerticies();
//	  //Check if all vertices of that triangle lie in any bounding box
//		  Vector3D a = vertInfo1[mesh1.vertex_1].pos;
//		  Vector3D b = vertInfo1[mesh1.vertex_2].pos;
//		  Vector3D c = vertInfo1[mesh1.vertex_3].pos;
//		  
//
//
//
//		  if(tBox2.containsVertex(a, offset))
//		  {
//				vert1 = true;
//			  return true;
//		  }else if(tBox2.containsVertex(b, offset))
//		  {
//			  vert2 = true;
//				return true;
//		  }else if(tBox2.containsVertex(c, offset))
//		  {
//			vert3 = true;
//			  return true;
//		  }
//		
//		
//
//
//
//		   return false;
//}
//
//
//
//
//void Collision::CollisionCheckForSub(std::vector< GameObject* > &vec_pGameObjects, int playerIndex,  bool &collision, Vector3D &origin)
//{
//	//check for collisions
//	/*Sphere* sphere = (Sphere*)vec_pGameObjects[playerIndex];
//
//	Vector3D playerPos = sphere->getPosition();
//	float radius = sphere->getRadius();
//*/
//	std::vector<Vector3D> closestPointsInEnv ; //It contains list of closest points of all objects
//	Physics::Point closestPoint ;
//	     
//	float distance = 99.0f; 
//	
//	  BoundingToBoundingBox(vec_pGameObjects[playerIndex], vec_pGameObjects[playerIndex+1], collision, origin);
//
//	
//}
//
//
//void Collision::CollisionResponeClamping(PLYELEMENT &mesh2, std::vector<PLYVERTEX> &vertInfo2, GameObject* &mesh1ObjSpace)
//{
//	/*
//	Clamp Collision - 
//		this technique is used to clamp velocity not the axis where collision has occured
//		steps :
//		1. Calculate normal of colliding triangle
//		2. Normalize that normal 
//		3. Calculate DotNormal as Object Velocity . Normal 
//		4. if DotNormal is not 0 , subtract (DotNormal * normal ) from object velocity 
//	*/
//
//
//
//	////Calculate Normal Vector m = Cross(b - a, c - a);
//	//Vector3D normal = Vector3D::CrossProduct(vertInfo2[mesh2.vertex_2].pos - vertInfo2[mesh2.vertex_1].pos, vertInfo2[mesh2.vertex_3].pos - vertInfo2[mesh2.vertex_1].pos);
//
//	////Normalize this 
//	//Vector3D::Normalize(normal.x, normal.y, normal.z);
//	//Vector3D::Normalize(normal.x, normal.y, normal.z);
//	//
//	////normal = normal * 2.0f;
//
//	////Find Velocity vector 
//	//Vector3D newVel = Vector3D() - mesh1ObjSpace->getVelocity() ; 
//
//	////Take Dot product
//	//float dotNormalProduct = Vector3D::DotProduct(mesh1ObjSpace->getVelocity(), normal);
//
//
//	////Set it 
//	//if(dotNormalProduct > 0.000f || dotNormalProduct < 0.000f)
//	//{
//	//  mesh1ObjSpace->setVelocity(mesh1ObjSpace->getVelocity() - (normal * dotNormalProduct));
//	//
//	//}
//	//
//
//
//}
//Where sphere2 is to be translated
bool Collision::SphereToSphereCollision(Sphere &sphere1 , Sphere &sphere2)
{
	Vector3D loc1 = sphere1.location;
	Vector3D loc2 = sphere2.location;

	float deltaX = loc1.x - loc2.x;
	float deltaY = loc1.y - loc2.y;
	float deltaZ = loc1.z - loc2.z;


	float distanceSqrd = ( (deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ)   ) ;

	float radius = sphere1.radius + sphere2.radius ;

	if(distanceSqrd <= (radius * radius)){

		Vector3D env ;

		env.x = 
			((sphere1.location.x * sphere2.radius) + (sphere2.location.x * sphere1.radius))  / (sphere1.radius + sphere2.radius);
 
		env.y = 
			((sphere1.location.y * sphere2.radius) + (sphere2.location.y * sphere1.radius))  / (sphere1.radius + sphere2.radius);

		env.z = 
			((sphere1.location.z * sphere2.radius) + (sphere2.location.z * sphere1.radius))  / (sphere1.radius + sphere2.radius);


		Vector3D dist =  sphere2.location - env ;
	
	

		Vector3D::Normalize( dist.x, dist.y,dist.z);
		
		dist = dist * sphere2.radius;
		
		

		Vector3D distToTraverse = env + dist;
		sphere2.location = distToTraverse;// newPoint;


		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::SphereToSphereCollisionVelTransfer(Sphere &sphere1 , Sphere &sphere2, Vector3D &pt)
{
	Vector3D loc1 = sphere1.location;
	Vector3D loc2 = sphere2.location;

	float deltaX = loc1.x - loc2.x;
	float deltaY = loc1.y - loc2.y;
	float deltaZ = loc1.z - loc2.z;


	float distanceSqrd = ( (deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ)   ) ;

	float radius = sphere1.radius + sphere2.radius ;

	if(distanceSqrd <= (radius * radius)){

			Vector3D env ;

		env.x = 
			((sphere1.location.x * sphere2.radius) + (sphere2.location.x * sphere1.radius))  / (sphere1.radius + sphere2.radius);
 
		env.y = 
			((sphere1.location.y * sphere2.radius) + (sphere2.location.y * sphere1.radius))  / (sphere1.radius + sphere2.radius);

		env.z = 
			((sphere1.location.z * sphere2.radius) + (sphere2.location.z * sphere1.radius))  / (sphere1.radius + sphere2.radius);


		Vector3D dist =  sphere2.location - env ;
	
	

		Vector3D::Normalize( dist.x, dist.y,dist.z);
		
		dist = dist * sphere2.radius;

		Vector3D distToTraverse =  env +dist;
		pt = env;

		//Normal Vec 
		sphere1.normalVec = sphere1.location - env;

		//Vector3D::Normalize(distToTraverse);
		//sphere2.location = distToTraverse;// newPoint;


		/*	Vector3D newVelocityA ; 
	    Vector3D newVelocityB ; 
		newVelocityA.x = ((sphere1.velocity.x * (sphere2.radius - sphere1.radius)) + (2 * sphere2.radius * sphere2.velocity.x)) / (sphere1.radius + sphere2.radius);
		newVelocityA.y = ((sphere1.velocity.y * (sphere2.radius - sphere1.radius)) + (2 * sphere2.radius *sphere2.velocity.y)) / (sphere1.radius + sphere2.radius);
		newVelocityA.z = ((sphere1.velocity.z * (sphere2.radius - sphere1.radius)) + (2 * sphere2.radius * sphere2.velocity.z)) / (sphere1.radius + sphere2.radius);
					  

		
		sphere1.velocity = newVelocityA;

		newVelocityB.x = ((sphere2.velocity.x * (sphere1.radius - sphere2.radius)) + (2 * sphere2.radius * sphere1.velocity.x )) / (sphere1.radius + sphere2.radius);
		newVelocityB.y = ((sphere2.velocity.y * (sphere1.radius - sphere2.radius)) + (2 * sphere2.radius * sphere1.velocity.y)) / (sphere1.radius + sphere2.radius);
		newVelocityB.z = ((sphere2.velocity.z * (sphere1.radius - sphere2.radius)) + (2 * sphere2.radius * sphere1.velocity.z)) / (sphere1.radius + sphere2.radius);

	
		sphere2.velocity = newVelocityB;*/

		 // get the mtd
		Vector3D delta = sphere2.location - sphere1.location;//(position.subtract(ball.position));
		float d = Vector3D::Magnitude(delta);
    // minimum translation distance to push balls apart after intersecting
		Vector3D mtd =  delta * (((sphere2.radius + sphere1.radius)-d)/d);//delta.multiply(((getRadius() + ball.getRadius())-d)/d); 


    // resolve intersection --
    // inverse mass quantities
		float im1 = 1 / sphere2.radius; 
    float im2 = 1 / sphere1.radius;

    // push-pull them apart based off their mass
	sphere2.location += (mtd * (im1 / (im1 + im2)));

    sphere1.location -= (mtd * (im1 / (im1 + im2)));

    // impact speed
	Vector3D v = sphere2.velocity - sphere1.velocity;
	Vector3D::Normalize( mtd);
	float vn = Vector3D::DotProduct(v,mtd);

    // sphere intersecting but moving away from each other already
    if (!(vn > 0.0f))
		{
	float restitution = 0.9f;
    // collision impulse
    float i = (-(1.0f + restitution) * vn) / (im1 + im2);
	Vector3D impulse = mtd * i;

    // change in momentum
    sphere2.velocity += impulse * im1;
	sphere1.velocity -= impulse * im2;
    //ball.velocity = ball.velocity.subtract(impulse.multiply(im2));
	}

		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::CubeToSphereCollision(Cube &cube, Sphere &sphere)
{
 float dmin = 0;

 Vector3D center = sphere.location;
 Vector3D bmin = cube.min;
 Vector3D bmax = cube.max;

    if (center.x < bmin.x) {
        dmin += pow(center.x - bmin.x, 2);
    } else if (center.x > bmax.x) {
        dmin += pow(center.x - bmax.x, 2);
    }

    if (center.y < bmin.y) {
        dmin += pow(center.y - bmin.y, 2);
    } else if (center.y > bmax.y) {
        dmin += pow(center.y - bmax.y, 2);
    }

    if (center.z < bmin.z) {
        dmin += pow(center.z - bmin.z, 2);
    } else if (center.z > bmax.z) {
        dmin += pow(center.z - bmax.z, 2);
    }

     if(dmin <= pow(sphere.radius, 2))
	 {
	 Vector3D dist =  sphere.location - cube.location ;
		Vector3D::Normalize( dist.x, dist.y,dist.z);
		
		dist = dist * sphere.radius;
		
		Vector3D env ;

		env.x = (center.x < bmin.x)? bmin.x : (center.x > bmax.x)? bmax.x : center.x;
		env.y = (center.y < bmin.y)? bmin.y : (center.y > bmax.y)? bmax.y : center.y;
		env.z = (center.z < bmin.z)? bmin.z : (center.z > bmax.z)? bmax.z : center.z;

		Vector3D distToTraverse = env + dist;
		sphere.location = distToTraverse;// newPoint;
	 
		  return true;
	 }
	 else
	 {
		return false;
	 }


	
}


bool Collision::MeshToSphereCollision(Shape &shape, Sphere &sphere, ModelData* shapeModel, Vector3D &pt)
{
	std::vector<PLYVERTEX> m_verticies = shapeModel->getVerticies();
	std::vector<PLYELEMENT> m_elements = shapeModel->getElements();
	float distance = 999.00f;
	std::vector<Physics::Point> closestPointsofObj ;
	Physics::Point closestPoint ;

	Vector3D velocityClamp;
	Vector3D normalVec;
	int count = 0;
	for(std::vector<PLYELEMENT>::iterator elementIter = m_elements.begin(); elementIter != m_elements.end(); elementIter++)
	{
		Vector3D vertex_1 = m_verticies[elementIter->vertex_1].pos;
		Vector3D vertex_2 = m_verticies[elementIter->vertex_2].pos;
		Vector3D vertex_3 = m_verticies[elementIter->vertex_3].pos;

		//Adding offset
		vertex_1 += shape.location;
		vertex_2 += shape.location;
		vertex_3 += shape.location;


		
		
		bool bIsInsideFace = false;
	

	   Physics::Point newclosestPoint = Physics::ClosestPtPointTriangle(sphere.location, vertex_1, vertex_2, vertex_3, bIsInsideFace );
	   float newDist = Physics::Distance(newclosestPoint,sphere.location);
	   
	   if(newDist < distance)
		{
			closestPoint = newclosestPoint;
		    distance = newDist;

		
			if(distance <= sphere.radius)
			{
				closestPointsofObj.push_back(newclosestPoint);

				 Vector3D velocity;
				VelocityToClampSphere(vertex_1, vertex_2, vertex_3 , sphere,  velocity);
				normalVec += Vector3D::CrossProduct(vertex_2 - vertex_1, vertex_3 - vertex_1);
				velocityClamp+=velocity;
				count++;
			}
		  
	  
	
		}


	}
	
	//
	//Calculate actual closest dist of that object 
	if( closestPointsofObj.size() > 0) //Collision has occured
	{
		Physics::Point sumObj(0.0f,0.0f,0.0f);
		for(int i = 0 ; i < closestPointsofObj.size(); i++)
		{
			sumObj += closestPointsofObj[i];
		}
		
		sumObj /= closestPointsofObj.size();
	


		Physics::Point dist =  sphere.location -sumObj ;
	    Vector3D::Normalize( dist.x, dist.y,dist.z);
		
		dist = dist * sphere.radius;
		

		Physics::Point distToTraverse = sumObj + dist;
		sphere.location = distToTraverse;// newPoint;


		velocityClamp /= count;
		normalVec /= count;
		sphere.velocity = velocityClamp;
		shape.normalVec = normalVec;
		
	m_verticies.clear();
	m_elements.clear();
	closestPointsofObj.clear();

	pt = sumObj;
		return true;
	}else
	{
	
	m_verticies.clear();
	m_elements.clear();
	closestPointsofObj.clear();
		return false;
	}


}


 bool Collision::CubeToCubeCollision(Cube &cube1, Cube &cube2)
 {
 //	//Check if Box1's max is greater than Box2's min and Box1's min is less than Box2's max
//	return((tBox1.getmaxX() + offset.x) > tBox2.getminX() &&
//		   (tBox1.getminX() + offset.x) < tBox2.getmaxX() &&
//		   (tBox1.getmaxY() + offset.y) > tBox2.getminY() &&
//		   (tBox1.getminY() + offset.y) < tBox2.getmaxY() &&
//		   (tBox1.getmaxZ() + offset.z) > tBox2.getminZ() &&
//		   (tBox1.getminZ() + offset.z) < tBox2.getmaxZ());
 	//Check if Box1's max is greater than Box2's min and Box1's min is less than Box2's max
	 if((cube1.max.x) > cube2.min.x &&
		(cube1.min.x) < cube2.max.x &&
		(cube1.max.y) > cube2.min.y &&
		(cube1.min.y) < cube2.max.y &&
		(cube1.max.z) > cube2.min.z &&
		(cube1.min.z) < cube2.max.z)
	 {
	//	Collision Response pending

 
	 return true;
	 }else
	 {
	 return false;
	 }

	//If not, it will return false
 }

 void Collision::VelocityToClampSphere(Vector3D &a, Vector3D &b, Vector3D &c,Sphere &sphere,  Vector3D &velocity)
 {
 	/*
	Clamp Collision - 
		this technique is used to clamp velocity not the axis where collision has occured
		steps :
		1. Calculate normal of colliding triangle
		2. Normalize that normal 
		3. Calculate DotNormal as Object Velocity . Normal 
		4. if DotNormal is not 0 , subtract (DotNormal * normal ) from object velocity 
	*/



	//Calculate Normal Vector m = Cross(b - a, c - a);
	Vector3D normal = Vector3D::CrossProduct(b - a, c - a);

	//Normalize this 
	Vector3D::Normalize(normal.x, normal.y, normal.z);
	Vector3D::Normalize(normal.x, normal.y, normal.z);
	
	//normal = normal * 2.0f;

	//Find Velocity vector 
	Vector3D newVel = Vector3D() - sphere.velocity; 

	//Take Dot product
	float dotNormalProduct = Vector3D::DotProduct(sphere.velocity, normal);


	//Set it 
	if(dotNormalProduct > 0.000f || dotNormalProduct < 0.000f)
	{
	 // mesh1ObjSpace->setVelocity(mesh1ObjSpace->getVelocity() - (normal * dotNormalProduct));
		velocity = sphere.velocity - (normal * dotNormalProduct);
	}
	
 }