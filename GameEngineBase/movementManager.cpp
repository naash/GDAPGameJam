#include "movementManager.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 
MovementManager::MovementManager()
{


}
MovementManager::~MovementManager()
{

}

void MovementManager::moveEuler(float deltaTime, Vector3D &position, Vector3D &velocity, Vector3D &acceleration)
{

	//using Euler's forward integration , we calculate position based on velocity
	Vector3D newPos = position+ velocity * deltaTime;
	position = newPos;



}


void MovementManager::moveRK4(float deltaTime, Vector3D &position, Vector3D &velocity, Vector3D &acceleration)
{
	//De accelerate 

	Vector3D vel1, vel2, vel3 , vel4 , pos1, pos2, pos3, pos4, acc1, acc2, acc3, acc4;
	
	//Step 1 (Same as euler)
	pos1 = position + velocity ;
	vel1 = velocity + acceleration;
	
	acc1 = vel1 - velocity; 
	
	//Step 2 
	pos2 = pos1 + vel1 * (deltaTime * 0.5);
	vel2 = vel1 + acc1 * (deltaTime * 0.5);
	
	acc2 = (vel2 - vel1 ) / (deltaTime * 0.5);
	
	//Step 3 
	pos3 = pos2 + vel2 * (deltaTime * 0.5);
	vel3 = vel2 + acc2 * (deltaTime * 0.5);
	
	acc3 = (vel3 - vel2 ) / (deltaTime * 0.5);
	
    //Step 3 
	pos4 = pos3 + vel3 * (deltaTime);
	vel4 = vel3 + acc3 * (deltaTime);

	acc4 = (vel4 - vel3 ) / (deltaTime);

	//Integrate ...........
	
	Vector3D dxdt =    ( vel1 +  (vel2 + vel3) * 2.0f + vel4 )* (1.0f / 6.0f);
    
    Vector3D dvdt =    ( acc1 + (acc2 + acc3) * 2.0f + acc4 ) * (1.0f / 6.0f);
		
	//Update Velocity and position
	
	position = position + (dxdt * deltaTime);
	

}

 void MovementManager::moveVerlet(float deltaTime,  Vector3D &position, Vector3D &velocity, Vector3D &acceleration, float &mTime)
{
	deltaTime = glm::min(deltaTime, 0.03f);
	mTime += deltaTime;
	float halfDt = deltaTime / 2.f;
	float dtSquared = deltaTime * deltaTime;

	

	// step 1: r(t+h) = r(t) + h * [v(t) + (h/2)*a(t)]
	position += (velocity+ acceleration * halfDt) * deltaTime;

	// step 2: v(t + h/2) = v(t) + (h/2)*a(t)
	velocity += acceleration * halfDt;

}

 void MovementManager::addForce(std::string type , Vector3D& value, Vector3D force ,float forceFactor)
 {
	if(type == "FRICTION")
	{
		value *= forceFactor;
	}else if(type == "GRAVITY")
	{
		value.y -= forceFactor;
	
	}else if(type == "WIND")
	{
		float windFactor = 1.0f + 0.4f * glm::sin(forceFactor);
		Vector3D accWind = force * windFactor;

		value += accWind;
	}
 
 }

 void MovementManager::setNewVelocity(float deltaTime, Vector3D &velocity, Vector3D &acceleration)
 {
	 velocity+= acceleration * deltaTime;
 }


 void MovementManager::rotateVerlet1(float deltaTime, rotationalVar* value)
 {
 /*Rotational Changes	*/
	 float angle = (glm::length(value->angular_velocity) + glm::length(value->angular_acceleration) * deltaTime * 0.5f) * deltaTime;
	if ( angle != 0.0f )
	{
		value->rotation = glm::rotate(value->rotation, angle, value->angular_velocity);

		glm::mat3 rotationMat = glm::toMat3(value->rotation);
		value->InvRotatedInertiaTensor = rotationMat * value->InertiaTensor  * glm::transpose(rotationMat);
		value->InvRotatedInertiaTensor = glm::inverse(value->InvRotatedInertiaTensor);
	}
 
 
 }
	//Integrate velocity based on deltaTime
 void MovementManager::rotateVerlet2(float deltaTime, rotationalVar* value)
 {
 //Rotational integration
	
	 value->angular_acceleration = value->InvRotatedInertiaTensor * value->Torque;
	value->angular_velocity += value->angular_acceleration * deltaTime * 0.5f;
	value->angular_velocity *= (1.f - (0.9f * deltaTime * 0.5f));
 
 
 }


 void MovementManager::ApplyAngularImpulse( rotationalVar* value,const glm::vec3 impulse, const glm::vec3& pt )
{

	value->angular_acceleration +=  value->InvRotatedInertiaTensor *  glm::rotate(glm::conjugate(value->rotation), glm::cross(impulse, pt));
	value->angular_velocity += value->angular_acceleration;
	
	float vel = glm::length(value->angular_velocity);
	if (vel > value->MaxAngularVelocity)
	{
		value->angular_velocity *= (value->MaxAngularVelocity / vel);
	}
}

 void MovementManager::ApplyForceAtPoint( rotationalVar* value,const glm::vec3 impulse, const glm::vec3& pt  )
{
	//value->angular_acceleration += f * MassInv;
	value->Torque = value->InvRotatedInertiaTensor * glm::cross(impulse, pt);
}