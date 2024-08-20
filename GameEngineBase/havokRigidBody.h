#ifndef _HAVOK_
#define _HAVOK_


#include "IPhysicsComp.h"
#include "Vector3D.h"
#include <glm/gtx/quaternion.hpp>

#include <Common/Base/hkBase.h>

#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012\Dynamics\Collide\ContactListener\hkpContactListener.h>

#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>

// Visual Debugger includes
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>


inline hkVector4 GetHKV4( const Vector3D& v )
{
	return hkVector4( v.x, v.y, v.z, 1.f );
}

enum eShapeType {
		BOX,
		SPHERE,
		CAPSULE,
		CYLINDER,
		PLANE,
		COMPLEX,
		CHASSIS
	};

class cHavokBodyDesc
{
public:
	
	  cHavokBodyDesc()
		: IsStatic(false)
		, Mass(1.f)
		, Restitution(0.f)
		, Friction(0.5f)
		, MaxAngularVelocity(200.f)
		, MaxLinearVelocity(200.f)
		, LinearDamping(0.f)
		, AngularDamping(0.01f)
		, enabled(false)
	{

	}
	// flags this as a static object, defaults to true
	bool IsStatic;
	// initial position
	Vector3D Position;
	// initial rotation
	glm::quat Rotation;
	// initial linear velocity vector m/s
	Vector3D LinearVelocity;
	// initial angular velocity vector rad/s
	Vector3D AngularVelocity;
	// Min extent for Phantom
	Vector3D minExtent;
	//Max Extent for phantom
	Vector3D maxExtent;
	// in m/s
	float MaxLinearVelocity;
	// in rad/s
	float MaxAngularVelocity;
	// linear motion damping
	float LinearDamping;
	// angular motion damping
	float AngularDamping;
	// mass of the body
	float Mass;
	// bounce factor
	float Restitution;
	// friction factor
	float Friction;

	//Scale
	float scale;
	//shape
	eShapeType shape;

	//physics enabled
	bool enabled;

	//contraints enabled
	bool constraintEnabled;
};

class cHavokRigidBody
{
public:
	
	struct sRigidBodyInfo
	{
		bool bMovable;
	};
	cHavokRigidBody( hkpRigidBody* pBody );

	~cHavokRigidBody();
	virtual void SetModelMatrix(glm::mat4* mat);
	virtual bool IsStatic();
	virtual bool IsDynamic();
	virtual bool GetPosition( Vector3D* pVec3 );
	virtual bool GetRotation( glm::quat* pRot );
	virtual bool SetPosition( const Vector3D& pos );
	virtual bool SetRotation( const glm::quat& rot );
	virtual void ApplyForce( float dt, const Vector3D& f );
	virtual void ApplyLinearImpulse( const Vector3D& im );
	virtual void ApplyTorque( float dt, const Vector3D& t );
	virtual void ApplyAngularImpulse( const Vector3D& im );

	hkpRigidBody* pHKBody;
	sRigidBodyInfo sInfo;
	hkpRigidBodyCinfo mInfo;
};


#endif