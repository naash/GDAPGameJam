#ifndef _ROTATIONAL_
#define _ROTATIONAL_

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


struct rotationalVar
{
	
		glm::quat rotation;
		glm::vec3 vecRotation;
		glm::vec3 angular_acceleration;
		glm::vec3 angular_velocity;


		float Friction;
		float Restitution;
		float MaxAngularVelocity;
		glm::mat3 InertiaTensor;
		glm::mat3 InvRotatedInertiaTensor;
		glm::vec3 Torque;
};

#endif