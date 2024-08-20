#include "havokPhyComp.h"
#include <glm/gtx/transform.hpp>
#include <iostream>


HavokPhyComp::HavokPhyComp(cHavokRigidBody* havokRigidBody)
{
	mBody = havokRigidBody;
	mBody->pHKBody->addEntityListener(&mEntityListener);
	mBody->pHKBody->addContactListener(&mCollisionListener);
}


HavokPhyComp::~HavokPhyComp()
{

}

void HavokPhyComp::SetModelMatrix( glm::mat4& mat )
{
  if(mEntityListener.Alive)
	{
		mBody->SetModelMatrix(&mat);
	}
}

bool HavokPhyComp::IsCloth()
{
	return false;
}

bool HavokPhyComp::IsStatic()
{
	return mBody->IsStatic();
}

bool HavokPhyComp::IsDynamic()
{
	return mBody->IsDynamic();
}

cHavokRigidBody* HavokPhyComp::GetBody()
{
	return mBody;
}


void HavokPhyComp::UpdatePhysicsAttrib(std::string type, Vector3D value)
	 {
		 mBody->ApplyForce(0.1,value);
	 }
    Vector3D HavokPhyComp::GetPhysicsAttrib(std::string type)
	 {    
		std::string LocType;
		 LocType = type;
		 if(LocType == "POSITION")
		 {
		 Vector3D pos;
		 mBody->GetPosition(&pos);
		 return pos;
		 }
		 else if(LocType =="ROTATION")
		 {
			 glm::quat* pRot = new glm::quat;
			mBody->GetRotation(pRot);
			Vector3D Obj;

			Obj.x = 2*acos(pRot->x);
			Obj.y = 2*acos(pRot->y);
			Obj.z = 2*acos(pRot->z);

			return Obj;
		 }



	 }
	void HavokPhyComp::UpdatePhysics(float deltaTime)
	 {}
	 void HavokPhyComp::RegisterPhyAttributes(Vector3D position, glm::quat rotation, float scale)
	 {}

	 void HavokPhyComp::cCollisionListener::collisionAddedCallback( const hkpCollisionEvent& event )
		{
		// do something about the collision beginning!
			//std::cout<<"Colliding!!"<<std::endl;

			colliding = true;
		}

	void HavokPhyComp::cCollisionListener::collisionRemovedCallback( const hkpCollisionEvent& event )
		{
		// do something about the collision ending!
		//	std::cout<<"Not Colliding!!"<<std::endl;
			colliding = false;
		}

	void HavokPhyComp::cCollisionListener::contactPointCallback( const hkpContactPointEvent& event )
		{
		//std::cout<<"Colliding!!"<<std::endl;
		}

	void HavokPhyComp::cEntityListener::entityRemovedCallback(hkpEntity* entity)
		{
			Alive = false;
			std::cout<<"Out of world"<<std::endl;
		}

	void HavokPhyComp::cEntityListener::entityAddedCallback(hkpEntity* entity)
		{
			Alive = true;
			std::cout<<"New to the world"<<std::endl;
		}


	bool HavokPhyComp::isAlive()
		{
			return mEntityListener.Alive ;
		}

	void HavokPhyComp::setAlive()
		{
			mEntityListener.Alive = true;
		}

	std::string HavokPhyComp::getType()
		{
			return "HAVOK";
		}

	 bool HavokPhyComp::isColliding()
		{
			return mCollisionListener.colliding;
		}