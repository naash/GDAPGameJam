#ifndef _MOV_MNGR_CH
#define _MOV_MNGR_CH

#include "Vector3D.h"
#include "rotationalVar.h"
#include <string>
/*
Called from physics components

used to simulate motion 
external forces 


*/
class MovementManager
{
public:
	MovementManager();
	~MovementManager();


	//linear Integration .......................................................
	static void moveEuler(float deltaTime, Vector3D &position, Vector3D &velocity, Vector3D &acceleration);
	static void moveRK4(float deltaTime,  Vector3D &position, Vector3D &velocity, Vector3D &acceleration);
	static void moveVerlet(float deltaTime, Vector3D &position, Vector3D &velocity, Vector3D &acceleration, float &mTime);
	//Integrate velocity based on deltaTime
	static void setNewVelocity(float deltaTime, Vector3D &velocity, Vector3D &acceleration);
	//..........................................................................

	//rotational Integration ..................................................
	static void rotateVerlet1(float deltaTime, rotationalVar* value);
	//Integrate velocity based on deltaTime
	static void rotateVerlet2(float deltaTime, rotationalVar* value);
	static void ApplyAngularImpulse( rotationalVar* value,const glm::vec3 impulse, const glm::vec3& pt );
	static void ApplyForceAtPoint( rotationalVar* value,const glm::vec3 impulse, const glm::vec3& pt  );


	//Add external forces ... Gravity , Friction etc
	static void addForce(std::string type , Vector3D& value,Vector3D force, float forceFactor = 1.0f);

	
private:

};

#endif