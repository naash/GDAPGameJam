#ifndef _HAVOK_COMP
#define _HAVOK_COMP

#include "IPhysicsComp.h"
#include "havokRigidBody.h"


class HavokPhyComp : public IPhysicsComp
{
public:
	class cEntityListener : public hkpEntityListener
	{
	public:
		cEntityListener():Alive(true){};
		virtual void entityRemovedCallback(hkpEntity* entity);
		virtual void entityAddedCallback(hkpEntity* entity);
	
		bool Alive;
	
	};

	class cCollisionListener : public hkpContactListener
	{
	public:

		cCollisionListener():colliding(false){};
		// collision begins
		virtual void collisionAddedCallback( const hkpCollisionEvent& event );
	
		// collision ends
		virtual void collisionRemovedCallback( const hkpCollisionEvent& event );
		
		//Collision callback
		virtual void contactPointCallback( const hkpContactPointEvent& event ) ;
		
		bool colliding;
	};

	HavokPhyComp(cHavokRigidBody* havokRigidBody);
	virtual ~HavokPhyComp();

	virtual void SetModelMatrix( glm::mat4& mat );

	virtual bool IsCloth();

	virtual bool IsStatic();

	virtual bool IsDynamic();

	virtual void UpdatePhysicsAttrib(std::string type, Vector3D value);
	virtual Vector3D GetPhysicsAttrib(std::string type);
	virtual void UpdatePhysics(float deltaTime);
	virtual void RegisterPhyAttributes(Vector3D position, glm::quat rotation, float scale);
  
	virtual std::string getType();
	virtual bool isColliding();
	bool isAlive();
	void setAlive();

	cHavokRigidBody* GetBody();
	cEntityListener mEntityListener;
	cCollisionListener mCollisionListener;
private:
	

	
	cHavokRigidBody* mBody;
	
};

#endif