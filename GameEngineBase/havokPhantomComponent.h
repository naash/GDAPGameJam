#ifndef _HAVOK_PHANTOM
#define _HAVOK_PHANTOM

#include <Common/Base/hkBase.h>
#include <Physics2012\Dynamics\Phantom\hkpAabbPhantom.h>
#include <Physics2012\Dynamics\Phantom\hkpPhantomOverlapListener.h>

#include "IMediator.h"
#include "IPhysicsComp.h"
#include "gameObject.h"

enum PhantonType
{
	CHECKPOINT = 0,
	POWERUP,


};

class HavokPhantomComp : public IPhysicsComp
{
public:

	class cOverlapListener : public hkpPhantomOverlapListener
	{
	public:
		bool Active;
		HavokPhantomComp* parent;
		cOverlapListener();
		virtual ~cOverlapListener();

		// collision begins
		virtual void  collidableAddedCallback(const hkpCollidableAddedEvent &event);

		// collision ends
		virtual void  collidableRemovedCallback(const hkpCollidableRemovedEvent &event);

	};


	PhantonType TYPE;

	HavokPhantomComp(hkpAabbPhantom* phantom);
	virtual ~HavokPhantomComp();
	
	bool Reached;
	float TimeReached;
	glm::vec3 HalfWidths;
	glm::vec3 Position;

	virtual void OnRegister();
	void Activate();
	void Deactivate();

	hkpAabbPhantom* mPhantom;
	IMediator* parentMediator;
	GameObject* parentObject;
	cOverlapListener mOverlapListener;

	int index;
	 void UpdatePhysicsAttrib(std::string type, Vector3D value);
	 Vector3D GetPhysicsAttrib(std::string type);
	 void UpdatePhysics(float deltaTime);
    void RegisterPhyAttributes(Vector3D position, glm::quat rotation, float scale);
	 void SetModelMatrix(glm::mat4& mat);
  
	 std::string getType();
	 bool isColliding();
  
};
#endif