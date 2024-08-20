#include "havokPhantomComponent.h"
#include "mediator.h"
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>

#include <iostream>
#include "global.h"

HavokPhantomComp::cOverlapListener::cOverlapListener()
{
	Active = true;
}

HavokPhantomComp::cOverlapListener::~cOverlapListener() {}

void HavokPhantomComp::cOverlapListener::collidableAddedCallback(const hkpCollidableAddedEvent &event)
{
	if (!Active) return;

	// do something about the collision beginning!
	// get points? tell the object we're colliding? maybe?
	((GameMediator*)parent->parentMediator)->Lock();
	//if ((GameMediator*)mediator)
	//{
		hkpRigidBody* body = hkpGetRigidBody(event.m_collidable);
		if (!body) return;

		std::cout << body->getUid() <<std::endl;
		
		if(parent->TYPE == CHECKPOINT && body->getFriction() < 1.0)
		{
		parent->parentObject->isActive = false;
		std::cout<<"Phantom collided"<<std::endl;
		//hudObject->score++;
		}
		/*cCheckPointNotification::Ptr note(new cCheckPointNotification(CheckpointId, ColliderId));
		physics->SendNotification(note);*/
		// tell the whole world we're colliding!
	//}
}

void HavokPhantomComp::cOverlapListener::collidableRemovedCallback(const hkpCollidableRemovedEvent &event)
{
	
}



HavokPhantomComp::HavokPhantomComp(hkpAabbPhantom* phantom)
: Reached(false), mPhantom(phantom)
{

	mOverlapListener.parent = this;

	phantom->addPhantomOverlapListener(&mOverlapListener);
	//Type = TYPE;
}

void HavokPhantomComp::Activate()
{
	mOverlapListener.Active = true;
}

void HavokPhantomComp::Deactivate()
{
	mOverlapListener.Active = false;
}

void HavokPhantomComp::OnRegister()
{
	//mOverlapListener.CheckpointId = this->GeID();
}

HavokPhantomComp::~HavokPhantomComp()
{

}


void HavokPhantomComp::UpdatePhysicsAttrib(std::string type, Vector3D value)
{



}
Vector3D HavokPhantomComp::GetPhysicsAttrib(std::string type)
{


	return Vector3D();
}
void HavokPhantomComp::UpdatePhysics(float deltaTime)
{



}
void HavokPhantomComp::RegisterPhyAttributes(Vector3D position, glm::quat, float scale)
{




}
void HavokPhantomComp::SetModelMatrix(glm::mat4& mat)
{



}
  
std::string HavokPhantomComp::getType()
{
	return "phantom";
}
bool HavokPhantomComp::isColliding()
{

	return false;

}