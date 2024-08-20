#ifndef _GameObject_HG_
#define _GameObject_HG_

#include <vector>
#include <string>
#include "Vector3D.h"

#include "modelData.h"
#include "IPhysicsComp.h"
#include "IMediator.h"
#include <Physics2012\Vehicle\hkpVehicle.h>


enum ButtonPressed
{
ACCELERATE = 0,
LEFT,
RIGHT,
BRAKES,
REVERSE,
HANDBRAKES,
DIRECTIONRESET
};

class GameObject 
{
public:
	GameObject();		// Default constructor 
	virtual ~GameObject();  

	virtual void Update( float deltaTime );

	unsigned int getID(void);

	 void attachModelData(ModelData* value);
	 ModelData* getModelData(int index);
	 float getMaxExtent();


	std::string getName();			// A helpful name
	std::wstring getPlyFileName();	// for rendering

	void setName(std::string value);			// A helpful name
	void setPlyFileName(std::string value);	// for rendering

	// Specular component (Shininess)
	void setSpecularShininess(float value);		// May way to make this a Vector3D, later (but need to update shader)
	void setSpecularStrength(float value);
	void setwireframe(bool value);

	bool hasChildObjects();

	void attachChildObject(GameObject* obj);

	std::vector<GameObject*> getChildObjects();
	std::vector<BoundingBox> GameObject::getBoundingBoxes();
	std::vector<BoundingBox> GameObject::getBoundingBoxesById(int id);
	//Only called by sub
	std::vector<GameObject*> childObjects;

	

	//for skyMap
	void setIsSkyMap(bool value);
	void setHasAlphaMap(bool value);
	void reCalculateBounds(glm::mat4 worldMatrix);
	//For Blend
	void setIsBlend(bool value);
	void setBlendVal(float value);

	//For Discard
	void setIsDiscard(bool value);

	//for TextureMix
	void setIsTextureMix(bool value);
	void setTextureMix(float value);
	

	//For Physics and Sim 2 ......................
	void render(glm::mat4& matWorld,glm::mat4& matView , Shader* shaderData, int pass,  glm::mat4& depthP = glm::mat4(1.0) , glm::mat4& depthV = glm::mat4(1.0) );
	void attachPhysics(IPhysicsComp* value);
	void updatePhysicAttribute(std::string type , Vector3D value);
	Vector3D getPhysicAttribute(std::string type);


	void attachMediator(IMediator* med);
	
	void setAsPlayer();
	bool getPlayer();
	

	IPhysicsComp* getPhyComp();

	//For HavokVehicle 

	void SetVehicleParams(std::string modelType);

	void setWheelPosition(IPhysicsComp* physicsComp, int wheelIndex);
	void updateWheels(std::vector<Vector3D> &tracks);
	void processUserInput(ButtonPressed input);
	 hkpVehicleInstance* m_vehicleInstance;
	 

	 //Stores which shader is used while rendring this
	std::string shaderName;
	bool isActive;
	int playerId;
protected:
	void m_Init(void);	// Called by the constructor. Set's everything to default state

	// Used to communicate with other objects
	//IMediator* m_pMediator;

	// Used to figure out what "state" the object is in
	std::string m_State;
	float extent; 
	unsigned int m_ID;	// Unique ID value
	// This will "pick" the "next" ID when object is created
	static unsigned int m_nextID;
	  ModelData* data;

	std::string name;			// A helpful name
	std::string plyFileName;	// for rendering
	// ADDED on September 29th, 2014

	// Specular component (Shininess)
	float specularShininess;		// May way to make this a Vector3D, later (but need to update shader)
	float specularStrength;
	bool isWireFrame;

	

	//For skymap
	bool isSkyMap;

	//For alpha map
	bool hasAlphaMap;

	// For Blending
	bool isBlend;
	float BlendVal;
	//For Discard
	bool isDiscard;
	//For TextureMix
	float textureMixval;
	bool isTextureMix;

	//Physics
	IPhysicsComp* physicsComp;

	//Mediator
	IMediator* med;

	

	bool isPlayer;


//For HavokVehicle
	std::vector<ModelData*> MDataVector;

	//Physics
	std::vector<IPhysicsComp*> physicsCompVector;

	hkReal inputY ; //Accelerate 
	hkReal inputX ; //Steer
	int Vcounter;
	int motionState;


};

#endif
