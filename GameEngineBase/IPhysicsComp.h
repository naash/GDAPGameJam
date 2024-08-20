#ifndef _IPHYSICS_H
#define _IPHYSICS_H

#include "Vector3D.h"
#include <glew.h>			// Because it complains when we don't include it
#include <freeglut.h>		// Because of the GLuint
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <string>
#include "vertexType.h"		// For CVertex_fXYZ_fRGB, etc.
#include "movementManager.h"
#include "collisionTest.h"
class IPhysicsComp
{
public:
	virtual ~IPhysicsComp(){};
	virtual void UpdatePhysicsAttrib(std::string type, Vector3D value) = 0;
	virtual Vector3D GetPhysicsAttrib(std::string type) = 0;
	virtual void UpdatePhysics(float deltaTime) = 0;
	virtual void RegisterPhyAttributes(Vector3D position, glm::quat rotation, float scale) = 0;
	virtual void SetModelMatrix(glm::mat4& mat)= 0;
  
	virtual std::string getType()=0;
	virtual bool isColliding() = 0;

};

#endif