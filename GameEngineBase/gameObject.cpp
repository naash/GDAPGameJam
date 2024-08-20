#include "GameObject.h"
#include "softBodyComp.h"
#include "mediator.h"


#include "global.h"


#include <Physics2012\Vehicle\DriverInput\Default\hkpVehicleDefaultAnalogDriverInput.h>
// Initial value of the first GameObject ID
// (i.e. the unique IDs of the objects will start at this number)
// Note that using an unsigned int, and assuming that it's 32 bits
//	means that it may potentially wrap around at some point. 
// (but you'd have to create 4 billion objects, first)
static const unsigned int FIRSTGAMEOBJECTID = 1000;
unsigned int GameObject::m_nextID = FIRSTGAMEOBJECTID;


// Called by the constructors
void GameObject::m_Init(void)
{
	// Assign ID here
	this->m_ID = this->m_nextID;   
	this->m_nextID++;	// Increment



	this->name = "no name";
	this->plyFileName = "";

	this->specularShininess = 1.0f;		// "Meh" shiny
	this->specularStrength = 1.0f;		// Not shiny
	this->isWireFrame = false;
	this->isSkyMap = false;
	this->hasAlphaMap = false;
	this->isBlend = false;
	this->isDiscard = false;
	this->isTextureMix = false;
	this->isPlayer = false;
	playerId = -1; //Not a player
	this->textureMixval = 0.0f;
	this->BlendVal = 1.0f;

	isActive = true;
	inputY = 0.0f; //Accelerate 
	inputX = 0.0f; //Steer
	motionState = 0;
	return;
}

GameObject::GameObject()
{
	this->m_Init();

	Vcounter = 0;


	return;
}



GameObject::~GameObject()
{
	//delete data;
	return;
}


void GameObject::Update( float deltaTime )
{
	// Insert behaviour code in here
	int sexyBreakpoint = 0;

	physicsComp->UpdatePhysics(deltaTime);


	return;
}

unsigned int GameObject::getID(void)
{
	return this->m_ID;
}

float GameObject::getMaxExtent()
{
	return data->getMaxExtent();
}



void GameObject::attachModelData(ModelData* value)
{
	data = value;
	this->MDataVector.push_back(value);
}

ModelData* GameObject::getModelData(int index)
{
	return MDataVector[index];
}


std::string GameObject::getName()
{
	return name;
}
std::wstring GameObject::getPlyFileName()
{
	return data->getFileName();
}





void GameObject::setName(std::string value)
{
	name = value;
}

void GameObject::setPlyFileName(std::string value)
{
	plyFileName = value;
}


// Specular component (Shininess)
void GameObject::setSpecularShininess(float value)
{
	specularShininess = value;
}
void GameObject::setSpecularStrength(float value)
{
	specularStrength = value;
}





std::vector<BoundingBox> GameObject :: getBoundingBoxes()
{
	std::vector<BoundingBox> resized = data->boundingboxes; 
	/* for (int i = 0; i < resized.size(); i++)
	{

	resized[i].setminX(resized[i].getminX() + position.x);
	resized[i].setmaxX(resized[i].getmaxX() + position.x);
	resized[i].setminY(resized[i].getminY() + position.y);
	resized[i].setmaxY(resized[i].getmaxY() + position.y);
	resized[i].setminZ(resized[i].getminZ() + position.z);
	resized[i].setmaxZ(resized[i].getmaxZ() + position.z);

	}*/
	return resized;
}
void GameObject::setwireframe(bool value)
{
	isWireFrame = value;
} 
//Added for matrix stack
bool GameObject::hasChildObjects()
{
	if (childObjects.size() > 0)
		return true;
	else
		return false;
}


void GameObject::attachChildObject(GameObject* obj)
{
	childObjects.push_back(obj);

}


std::vector<GameObject*> GameObject::getChildObjects()
{

	return childObjects;

}


std::vector<BoundingBox> GameObject::getBoundingBoxesById(int id)
{
	std::vector<int> copyIndex = data->boundingBoxgrp[id];


	std::vector<BoundingBox> resized ; 
	for(int i = 0 ; i < copyIndex.size() ; i++)
	{
		BoundingBox b = data->boundingboxes[copyIndex[i]];

		/*   b.setminX(b.getminX() + position.x);
		b.setmaxX(b.getmaxX() + position.x);
		b.setminY(b.getminY() + position.y);
		b.setmaxY(b.getmaxY() + position.y);
		b.setminZ(b.getminZ() + position.z);
		b.setmaxZ(b.getmaxZ() + position.z);*/


		resized.push_back(b);
	}


	return resized;
}



void GameObject::setIsSkyMap(bool value)
{
	isSkyMap = value;
}
void GameObject::setIsBlend(bool value)
{

	isBlend = value;
}
void GameObject::setIsDiscard(bool value)
{

	isDiscard = value;
}
void GameObject::setIsTextureMix(bool value)
{

	isTextureMix = value;
}


void GameObject::setTextureMix(float value)
{
	textureMixval = value;
}
void GameObject::setBlendVal(float value)
{

	BlendVal = value;
}

void GameObject::setHasAlphaMap(bool value)
{
	hasAlphaMap = value;
}


void GameObject::reCalculateBounds(glm::mat4 worldMatrix)
{
	data->reCalculateBounds(worldMatrix);

}

void GameObject::attachPhysics(IPhysicsComp* value)
{
	physicsComp = value;
	this->physicsCompVector.push_back(value);
}



void GameObject::render(glm::mat4& matWorld,glm::mat4& matView, Shader* shaderData, int pass ,  glm::mat4& depthP, glm::mat4& depthV )
{

	if(isActive)
	{


		//Pack data to be sent to shader   /////////////////////////////////////////////////////////////
		std::map<std::string , UniformData> uniformData;




		if(pass == 1)
		{
			if (isWireFrame)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//GL_FILL
			}


			//Loops through all vectors 
			for(int i = 0 ; i < MDataVector.size(); i++)
			{
				UniformData data;
				matWorld = glm::mat4(1.0);
				MDataVector[i]->activateTextures(uniformData);

				//physicsComp->SetModelMatrix(mat);
				physicsCompVector[i]->SetModelMatrix(matWorld);

				data.mat4Data = matWorld;
				uniformData["WorldMatrix"] = data;

				data.mat4Data = matView;
				uniformData["ViewMatrix"] = data;



				if(shaderName == "simple")
				{


					glm::mat4 biasMatrix(
						0.5, 0.0, 0.0, 0.0,
						0.0, 0.5, 0.0, 0.0,
						0.0, 0.0, 0.5, 0.0,
						0.5, 0.5, 0.5, 1.0
						);
					
					glm::mat4 depthMVP = depthP * depthV * matWorld;
					glm::mat4 depthBiasMVP = biasMatrix * depthMVP;
					data.mat4Data = depthBiasMVP;
					uniformData["depthMVP"] = data;



				}



				shaderData->setUniformVariablesInBulk(uniformData);

				MDataVector[i]->render();
				if(this->name.substr(0,4) == "Soft")
				{
					CVertex_fXYZW* verts = MDataVector[i]->beginMapping();
					unsigned int numVerts = MDataVector[i]->GetNumberOfVerticies();
					for (unsigned int idxVert = 0; idxVert < numVerts; idxVert++)
					{
						((SoftBodyPhyComp*)physicsCompVector[i])->GetPosition(idxVert, verts[idxVert]);
					}

					MDataVector[i]->endMapping();
				}

			}
		}
		else if(pass == 2) //Final Pass
		{
			//Render only quad here

			//Pack data to be sent to shader   /////////////////////////////////////////////////////////////
			std::map<std::string , UniformData> uniformData;
			UniformData data;


			

			//Pass 1 for depth texture
			//Loops through all vectors 
			for(int i = 0 ; i < MDataVector.size(); i++)
			{
				//MDataVector[i]->activateTextures(uniformData);
				physicsCompVector[i]->SetModelMatrix(matWorld);
				UniformData data;
				data.mat4Data = matWorld;
				uniformData["WorldMatrix"] = data;



				data.mat4Data = matView;
				uniformData["ViewMatrix"] = data;

				//shaderData[vec_pRenderedObjects[index]->shaderName]->setUniformVariablesInBulk(uniformData);
				myGlobalShader->setUniformVariablesInBulk(uniformData, true);

				MDataVector[i]->render();
			}


		}
		else if(pass == 3)
		{
			//Pack data to be sent to shader   /////////////////////////////////////////////////////////////
			std::map<std::string , UniformData> uniformData;


			for(int i = 0 ; i < MDataVector.size(); i++)
			{
				//MDataVector[i]->activateTextures(uniformData);
				physicsCompVector[i]->SetModelMatrix(matWorld);
				UniformData data;

				glm::mat4 depthMVP = depthP * depthV * matWorld;

				data.mat4Data = depthMVP;

				::myGlobalShader->setUniformVariable("depthMVP",data, false);


				//shaderData[vec_pRenderedObjects[index]->shaderName]->setUniformVariablesInBulk(uniformData);
				//myGlobalShader->setUniformVariablesInBulk(uniformData);

				MDataVector[i]->render();
			}


		}else if(pass == 4)
		{
			if (isWireFrame)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//GL_FILL
			}


			//Loops through all vectors 
			for(int i = 0 ; i < MDataVector.size(); i++)
			{
				UniformData data;
				matWorld = glm::mat4(1.0);
				MDataVector[i]->activateTextures(uniformData);

				//physicsComp->SetModelMatrix(mat);
				matWorld = glm::scale(matWorld, glm::vec3(1.0,-1.0,1.0));
				physicsCompVector[i]->SetModelMatrix(matWorld);

				


				data.mat4Data = matWorld;
				uniformData["WorldMatrix"] = data;

				data.mat4Data = matView;
				uniformData["ViewMatrix"] = data;



				if(shaderName == "simple")
				{


					glm::mat4 biasMatrix(
						0.5, 0.0, 0.0, 0.0,
						0.0, 0.5, 0.0, 0.0,
						0.0, 0.0, 0.5, 0.0,
						0.5, 0.5, 0.5, 1.0
						);
					
					glm::mat4 depthMVP = depthP * depthV * matWorld;
					glm::mat4 depthBiasMVP = biasMatrix * depthMVP;
					data.mat4Data = depthBiasMVP;
					uniformData["depthMVP"] = data;



				}



				shaderData->setUniformVariablesInBulk(uniformData);

				MDataVector[i]->render();
				if(this->name.substr(0,4) == "Soft")
				{
					CVertex_fXYZW* verts = MDataVector[i]->beginMapping();
					unsigned int numVerts = MDataVector[i]->GetNumberOfVerticies();
					for (unsigned int idxVert = 0; idxVert < numVerts; idxVert++)
					{
						((SoftBodyPhyComp*)physicsCompVector[i])->GetPosition(idxVert, verts[idxVert]);
					}

					MDataVector[i]->endMapping();
				}

			}
		}



	}

}


void GameObject::updatePhysicAttribute(std::string type , Vector3D value)
{
	//if(name == "Vehicle")
	//{

	//	if(type=="ACCELERATION")
	//	{

	//		m_vehicleInstance->getChassis()->activate();
	//		std::cout<<"Speed "<<m_vehicleInstance->calcKMPH()<<std::endl;
	//		hkReal deltaX = 0.0f;
	//		hkReal deltaY = 0.0f;
	//		const hkReal steerSpeed     =  10.0f;
	//		hkpVehicleDriverInputAnalogStatus* deviceStatus = (hkpVehicleDriverInputAnalogStatus*)m_vehicleInstance->m_deviceStatus;

	//		if(value.z < 0.0)
	//		{
	//			//Accelerate 
	//			std::cout<<"Accelerate"<<std::endl;
	//			deltaY = 0.5f;
	//			//if(m_vehicleInstance->m_torque < 20.0f)
	//			//m_vehicleInstance->m_torque += 0.5f;
	//		}
	//		else if(value.x < 0.0)
	//		{
	//			//Turn Left
	//			std::cout<<"Turn Left"<<std::endl;



	//			deltaX -= steerSpeed;



	//			deviceStatus->m_positionX += hkMath::clamp( deltaX, hkReal(-5.0f), hkReal(5.0f));
	//		}
	//		else if(value.x > 0.0)
	//		{
	//			//Turn right
	//			std::cout<<"Turn Right"<<std::endl;



	//			deltaX += steerSpeed;




	//		}
	//		else
	//		{
	//			//Brakes
	//			std::cout<<"Brakes !!"<<std::endl;
	//			deltaY = -0.5f;


	//			//if(m_vehicleInstance->m_torque > 0.0f)
	//			//m_vehicleInstance->m_torque -= 0.5f;
	//		}

	//		deviceStatus->m_positionY += deltaY;//hkMath::clamp( deltaY, hkReal(-1.0f), hkReal(1.0f));    
	//		deviceStatus->m_positionX += deltaX;//hkMath::clamp( deltaX, hkReal(-1.0f), hkReal(1.0f));
	//		std::cout<<"Turning "<<deviceStatus->m_positionX<<std::endl;
	//		std::cout<<"Acceleration "<<deviceStatus->m_positionY<<std::endl;

	//	}

	//}
	//else
	//{
	//	physicsComp->UpdatePhysicsAttrib(type, value);
	//}


}

Vector3D GameObject::getPhysicAttribute(std::string type)
{

	//return physicsComp->GetPhysicsAttrib(type);
	return physicsCompVector[0]->GetPhysicsAttrib(type);
}

void GameObject::attachMediator(IMediator* p_med)
{
	med = p_med;

}

void GameObject::setAsPlayer()
{
	this->isPlayer = true;
}
bool GameObject::getPlayer()
{
	return this->isPlayer;
}


IPhysicsComp* GameObject::getPhyComp()
{
	return physicsComp;
}


//For Havok Vehicle ------>

void buildVehicle()
{
}



void GameObject::setWheelPosition(IPhysicsComp* physicsComp, int wheelIndex)
{
	if(m_vehicleInstance != NULL)
	{
		hkVector4 pos;
		hkQuaternion rot;

		m_vehicleInstance->calcCurrentPositionAndRotation(m_vehicleInstance->getChassis(),m_vehicleInstance->m_suspension,wheelIndex,pos,rot);

		glm::quat rotation;
		rotation.x = rot.getComponent<0>();
		rotation.y = rot.getComponent<1>();
		rotation.z = rot.getComponent<2>();
		rotation.w = rot.getComponent<3>();


		//	std::cout<<"Position of wheel "<<wheelIndex<<" x : "<<pos.getComponent(0)<<" y "<<pos.getComponent(1)<<" z "<<pos.getComponent(2)<<std::endl;

		//	std::cout<<"Rotation of wheel "<<wheelIndex<<" x : "<<rot.m_vec.getComponent(0)<<" y "<<rot.m_vec.getComponent(1)<<" z "<<rot.m_vec.getComponent(2)<<std::endl;
		//Vector3D(rot.m_vec.getComponent(0),rot.m_vec.getComponent(1),rot.m_vec.getComponent(2))
		physicsComp->RegisterPhyAttributes(Vector3D(pos.getComponent(0),pos.getComponent(1),pos.getComponent(2)), rotation, 1.0);

	}

}


void GameObject::updateWheels(std::vector<Vector3D> &tracks)
{

	//hkpTyremarksInfo* info =  this->m_vehicleInstance->m_tyreMarks;


	

	for(int i = 0 ; i < physicsCompVector.size(); i++)
	{
		if(physicsCompVector[i]->getType() == "BASE")
		{
			this->setWheelPosition(physicsCompVector[i],i-1);

			/*hkVector4* tireOrigin = new hkVector4();
			info->getWheelTyremarksStrips(this->m_vehicleInstance, i-1,tireOrigin);

			tracks.push_back(Vector3D(tireOrigin->getComponent(0),tireOrigin->getComponent(1),tireOrigin->getComponent(2)));*/
		}
	}

}



void GameObject::processUserInput(ButtonPressed input)
{
	

	//
	// Update controller "position" within range [-1, 1] for both X, Y directions.
	//
	hkpVehicleDriverInputAnalogStatus*	deviceStatus = (hkpVehicleDriverInputAnalogStatus*)m_vehicleInstance->m_deviceStatus;

	const hkReal steerSpeed     = 2.0f;// * 0.1f;
	const hkReal backSteerSpeed = 10.0f * 0.1f;
	hkReal deltaY = -inputY  * 0.2f;
	hkReal deltaX = -inputX  * backSteerSpeed;

	if ( (input == ACCELERATE))  // Add HKG_PAD_BUTTON_0 to restore pre-Havok 5.5 control
	{
		// Accelerate.
		deltaY = -0.1f;// Acceleration down to this value from 0.1



		inputY = hkMath::clamp( inputY+deltaY, hkReal(-0.3f), hkReal(0.3f));
		deviceStatus->m_positionY = inputY;
	}
	else if (input == BRAKES )
	{
		// Brake/reverse.
		deltaY = 0.1f;


		inputY = hkMath::clamp( inputY+deltaY, hkReal(-0.3f), hkReal(0.3f));
		deviceStatus->m_positionY = inputY;// it should halt the car (Acceleration becomes zero)
	}

	if ( input == RIGHT)
	{
		// Turn left.
		if ( inputX >= 0.0f){	deltaX = 0.0f;	}
		deltaX += steerSpeed;

		inputX = hkMath::clamp( inputX+deltaX, hkReal(-0.3f), hkReal(0.3f));

		deviceStatus->m_positionX = inputX;
	}
	else if (input ==LEFT  )
	{
		// Turn right.
		if ( inputX <= 0.0f){	deltaX = 0.0f;	}
		deltaX -= steerSpeed;

		inputX = hkMath::clamp( inputX+deltaX, hkReal(-0.3f), hkReal(0.3f));

		deviceStatus->m_positionX = inputX;
	}
	else if (input == HANDBRAKES)
	{

		deviceStatus->m_positionY = 0;
		deviceStatus->m_positionX = 0;

	}
	else if (input == DIRECTIONRESET)
	{
	
		deviceStatus->m_positionX = 0;
	}

	//// add analog controls
	//{
	//	deltaY -= .2f * pad->getStickPosY(0);

	//	hkReal x = pad->getStickPosX(1);
	//	//if ( x < 0 && inputXPosition <= 0.0f){	deltaX = 0.0f;	}
	//	//if ( x > 0 && inputXPosition >= 0.0f){	deltaX = 0.0f;	}
	//	deltaX += x * backSteerSpeed;
	//}





	// Now -1 <= m_inputXPosition <= 1 and
	// -1 <= m_inputYPosition <= 1





	//std::cout<<"input Y "<<deviceStatus->m_positionY<<std::endl;
	//std::cout<<"torque "<<m_vehicleInstance->m_torque<<std::endl;
	// AutoReverse
	deviceStatus->m_reverseButtonPressed = ( input == REVERSE) != 0;

	// Handbrake.
	//hkprintf( "%f %f\n", *inputXPosition, *inputYPosition);
	deviceStatus->m_handbrakeButtonPressed = (input == HANDBRAKES) != 0;
	///[CODE steerCode]>
}