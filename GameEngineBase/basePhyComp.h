#ifndef _BASE_PHY
#define _BASE_PHY

#include "IPhysicsComp.h"
#include "rotationalVar.h"
#include "IMediator.h"
#include <iostream>
class BasePhyComp : public IPhysicsComp
{
public :

	BasePhyComp();
	~BasePhyComp();

	virtual void UpdatePhysics(float deltaTime);
	virtual void UpdatePhysicsAttrib(std::string type, Vector3D value);
	 Vector3D GetPhysicsAttrib(std::string type);
	void RegisterPhyAttributes(Vector3D position, glm::quat rotation, float scale);
	virtual void SetModelMatrix(glm::mat4& mat);
	virtual void CheckForCollision(float deltaTime);
	std::string getType();
	bool isColliding();
		IMediator* mediator;
		bool physicsEnabled;
		
		std::string shape;
		float radius;
		Vector3D min;
		Vector3D max;
		bool collided;
		rotationalVar* rot ;
protected:

		float scale;
		Vector3D position;
		Vector3D prevPosition;
		Vector3D velocity;

		Vector3D acceleration;

		
	
	
		glm::mat3 GetInertiaTensor();
};

#endif