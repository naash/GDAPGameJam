#ifndef _ParticleEmitter_HG_
#define _ParticleEmitter_HG_

// Manage all the particles
#include "Vector3D.h"
#include <vector>



class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	void SetLocation( Vector3D newLocation );
	void SetAcceleration( Vector3D newAcceleration );
	void GenerateParticles( int numParticles, Vector3D initVelocity,
		                    float maxDistanceFromSouce, 
							float startingAge,	// Added
							bool bRespawn );	// Added
	void SetRespawn( bool bNewRespawn );		// Added
	void Update( float deltaTime );

	// "Shouldn't" make this public, but for time, we'll do it
	class CParticle
	{
	public:
		CParticle() {};	// construtor defined here
		~CParticle() {};	// 
		Vector3D position;		// c'tor sets these to zeros
		Vector3D velocity;		// c'tor sets these to zeros
		float age;
	};
	// Returns any "alive" particles
	void GetParticles( std::vector< CParticle > &vecLiveParticles ); 
	bool Alive();
private:
	std::vector< CParticle > m_myParticles;	
	Vector3D m_location;
	Vector3D m_acceleration;
	// 
	Vector3D m_initVelocity;
	float m_maxDistanceFromSouce;
	float m_startingAge;
	bool m_bRespawn;
	bool aliveParticles;
	// Called internally
	void m_CreateParticle(CParticle &tempParticle);
};

#endif
