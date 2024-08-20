#include "havokRigidBody.h"


cHavokRigidBody::cHavokRigidBody( hkpRigidBody* pBody )
{
	pHKBody = pBody;
}

cHavokRigidBody::~cHavokRigidBody()
{

}

bool cHavokRigidBody::GetPosition( Vector3D* pVec3 )
{
	hkVector4 pos = pHKBody->getPosition();
	pVec3->x = pos.getComponent(0);
	pVec3->y = pos.getComponent(1);
	pVec3->z = pos.getComponent(2);
	return true;
}

bool cHavokRigidBody::GetRotation( glm::quat* pRot )
{
	hkQuaternion quat = pHKBody->getRotation();
	pRot->x = quat.getComponent<0>();
	pRot->y = quat.getComponent<1>();
	pRot->z = quat.getComponent<2>();
	pRot->w = quat.getComponent<3>();
	return true;
}

bool cHavokRigidBody::IsStatic()
{
	return !sInfo.bMovable;
}

bool cHavokRigidBody::IsDynamic()
{
	return sInfo.bMovable;
}

void cHavokRigidBody::ApplyForce( float dt, const Vector3D& f )
{

	pHKBody->getWorld()->lock();

	hkReal hkDt = dt;
	hkVector4 hkF = GetHKV4(f);
	pHKBody->applyForce( hkDt, hkF );

	pHKBody->getWorld()->unlock();
}

void cHavokRigidBody::ApplyLinearImpulse( const Vector3D& im )
{
	hkVector4 hkIm = GetHKV4(im);
	pHKBody->applyLinearImpulse( hkIm );
}

void cHavokRigidBody::ApplyTorque( float dt, const Vector3D& t )
{
	hkReal hkDt = dt;
	hkVector4 hkT = GetHKV4(t);
	pHKBody->applyTorque( hkDt, hkT );
}

void cHavokRigidBody::ApplyAngularImpulse( const Vector3D& im )
{
	hkVector4 hkIm = GetHKV4(im);
	pHKBody->applyAngularImpulse( hkIm );
}

bool cHavokRigidBody::SetPosition( const Vector3D& pos )
{
	hkVector4 hkPos = GetHKV4( pos );
	pHKBody->setPosition( hkPos );
	return true;
}

bool cHavokRigidBody::SetRotation( const glm::quat& rot )
{
	hkQuaternion q = hkQuaternion( rot.x, rot.y, rot.z, rot.w );
	pHKBody->setRotation( q );
	return true;
}

void cHavokRigidBody::SetModelMatrix( glm::mat4* mat )
{
	hkMatrix4 m;
	hkTransform transform;
	if(pHKBody->getWorld() != 0)
	{
	pHKBody->approxCurrentTransform(transform);
	
	m.set( transform );
	memcpy(mat, &m, sizeof(float)*16);
	}
}
