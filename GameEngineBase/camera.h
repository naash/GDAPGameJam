#ifndef _CCamera_HG_
#define _CCamera_HG_

#include "Vector3D.h"		// Basically a vec3

//#include "IMediator.h"		// Allow camera to find game objects

class CCamera 
{
public:
	CCamera();
	~CCamera();

//	void SetMediator( IMediator* pTheMediator );

	Vector3D eye;
	Vector3D offset;
	Vector3D target;
	Vector3D up;

	// Follow at speed up to a certain distance
	void Follow( unsigned int ID_to_follow, float followSpeed, 
		         float minDistance, float minHeight );
	// Called in the "idle" or "simulation step"
	void Update( float deltaSeconds );

	bool bIsFollowing;
	unsigned int object_to_follow_ID;
	float minFollowDistance;
	float followSpeed;
	float minHeight;

	// Maybe you can fill these out if you can't sleep tonight...
	void MoveX( float delta );
	void MoveY( float delta );
	void MoveZ( float delta );

private:
	//IMediator* m_pTheMediator;
};

#endif