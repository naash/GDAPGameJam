#ifndef _C_Game_OBJ_CH
#define _C_Game_OBJ_CH

#include "IMediator.h"

#include "gameObject.h"
#include "textureData.h"
#include "IPhysicsComp.h"
#include "havokRigidBody.h"

#include <vector>
#include <string>

#include "particleGen.h"

//file loader puts all data in this box and sends it to mediator
struct ObjectBox
{
	std::string ObjectType;
	std::string shaderName;
	std::vector<std::wstring> fileNames;
	std::string texture;
	Vector3D color;
};

//file loader puts all data in this box and sends it to mediator
struct ShaderBox
{
	std::string shaderName;
	std::map<GLenum, std::string> components;
	std::map<std::string, UniformType> uniformVarType;
};


class hkpConvexVerticesShape;

class GameMediator : public IMediator
{
public:
	GameMediator();
	~GameMediator();


	static hkpConvexVerticesShape* createChassisShape();
	static hkpConvexVerticesShape* createChassisShape(ModelData* data );

	void createTextures(std::string textureType,std::string textureName);
	void createSkybox(std::vector<std::string> textureName,std::string textureType);
	GameObject* createObject(ObjectBox data);
	void createParticles(Vector3D origin);
	void createShader(ShaderBox data);
	void createModel(std::wstring fileName,std::string texture, std::string modelMode , std::string physics ,std::string alText);
	virtual bool UpdateObjectAttribVector(std::string type, Vector3D value,  GameObject* &object);
	virtual bool UpdateObjectPositionByID( Vector3D newPosition ,  GameObject* &object);
	virtual bool UpdateObjectRadiusByID( float radius , GameObject* &object);
	virtual bool UpdateObjectScaleByID( float newScale ,  GameObject* &object);
	virtual bool UpdateObjectVelocityByID(  Vector3D newVelocity ,   GameObject* &object);
	virtual bool UpdateObjectAccelerationByID(  Vector3D newAcceleration ,   GameObject* &object);
	virtual bool UpdateObjectRotationByID(  Vector3D newRotation ,  GameObject* &object );


	virtual void createBoundingBox(GameObject* &object, std::vector <GameObject*> &debugList, std::string type, Vector3D offset);
	virtual bool GameMediator::TestScale(float newScale, GameObject* &object);

	virtual void setSphereId(int value);
	virtual int getSphereId();


	virtual void AttachPhysics(Vector3D position, Vector3D rotation, float scale, std::string phyType, std::string shape, GameObject* &object, softBodyAttribs a );
	//....................Added in Project 3

	//Fetch player id 
	GLuint& getPlayerId(int index);

	//Fetch skybox id
	GLuint& getSkyBoxId();

	void setPlayerId(GLuint value);
	void setSkyBoxId(GLuint value);
	//....................
	std::vector<IPhysicsComp*> fetchPhyComp();
	std::vector<ModelData*> fetchModelComp();
	//TextureData* fetchTextureAtIndex(int index);
	std::vector<GameObject*> fetchSceneList();
	std::vector<GameObject*> fetchParticleList();
	//.....................Havok stuff............................
	virtual void RenderingBegin();
	virtual void RenderingEnd();
	void Lock();
	void Unlock();
	void initHavok();
	void shutdown();
	virtual void AttachPhysics(GameObject* &object, softBodyAttribs a , cHavokBodyDesc &r, int index);
	virtual void AttachPhantom(GameObject* &object, softBodyAttribs a , cHavokBodyDesc &r, int index);
	virtual void Update( float dt );
	//............................................................
	void mediatorUserInput(ButtonPressed input, int index);
	//To fetch Shaders
	std::map<std::string , Shader*> fetchShaders();
	TextureData* getTextureByName(std::string);



		//For particles 
	void genParticles(Vector3D origin);

private:
	std::vector <ModelData*> modelList;
	std::map <std::string, TextureData*> textureList; 
	std::vector <IPhysicsComp*> physicComp;
	std::vector <GameObject*> sceneList;
	std::vector <GameObject*> particleList;
	std::map<std::string , Shader*> shaderStore;
	unsigned int SphereId;

	//Added in Project 3 
	std::vector<GLuint> player_ids;
	GLuint skybox_id;


	//Vector to store particle objects
	std::vector<ParticleEmitter*> particleObj;

	//Havok stuff
	void InitMemory();
	void InitWorld();
	void InitVDB();
	void StepHavok(hkReal timeStep);


	hkpPhysicsContext* mPhysicsContext;
	bool mVDBEnabled;
	hkVisualDebugger* mVisualDebugger;

	hkJobQueue* mJobQueue;
	hkJobThreadPool* mThreadPool;

	hkpWorld* mWorld;			// Physics world.
	hkpWorldCinfo mWorldInfo; // Info about global simulation parameters.
	//.................
};

#endif