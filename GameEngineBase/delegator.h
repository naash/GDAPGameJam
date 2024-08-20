#ifndef _DELEGATOR_CH
#define _DELEGATOR_CH

#include "gameObject.h"

#include "fileDataLoader.h"
#include "mediator.h"
#include "movementManager.h"
#include "collisionTest.h"

#include <vector>
#include <string>


class Delegator 
{
public:
	Delegator();
	~Delegator();

	//To create scene from external file for single player 
	void createScene(CShaderUniformVariables &g_ShaderUniformVariables, int single);



	//To create Game Object and return its ID
	unsigned int createObject(std::string ObjectType,std::string fileName,int textureName, std::string modelMode = "excl");


	//To update something in object (use vecAttrib to update vector and param to update float)
	void updateObject(std::string UpdateType, Vector3D vecAttrib,unsigned int ID, float param = 1.0f);


	std::wstring ASCII_to_Unicode( std::string ASCIIstring );

	//Fetch list of game objects created.
	std::vector <GameObject*> getSceneList();

	//Fetch list of game particles created.
	std::vector <GameObject*> getParticleList();

	//Update position, orientation , Object specific changes over deltaTime
	void simulation(float deltaTime);

	//Fetch player id 
	GLuint getPlayerId(int index);

	//Fetch skybox id
	GLuint getSkyBoxId();
	//Fetch Sphere Id
	int getSphereId();
	//Fetch list of player objects
	std::vector <GLuint> getMyPieces();

	//Fetch List index
	GLuint getMyPiecesIndex();

	void setMyPiecesIndex(GLuint value);
	std::vector <GameObject*> getDebugObject();


	//For particles 
	void genParticles(Vector3D origin);

	//To generate Texture independently 
	void loadTextures();

	//To generate Skybox texture
	void loadSkyBox(std::vector<std::string> textureName,std::string textureType);

	//fetch Mixture Texture

	void setTextureMixVal(std::string ObjectType, float value);
	//FETCH bLEND VALUE
	void setBlendVal(std::string ObjectType, float value);

	//To fetch  position
	Vector3D getSkyboxPos();
	Vector3D getPlayerPos(int index);
	void userInput(ButtonPressed input, int index);

	//To call any internal function
	void callFunc(std::string type);

	//To fetch Shaders
	std::map<std::string , Shader*> getShaders();

	//To fetch texture from name
	TextureData* getTexture(std::string);
	Vector3D Delegator::getPlayerRotation(int index);
private:
	//std::vector <GameObject*> sceneList;
	std::vector <GameObject*> particleList;
	std::vector <GLuint> myPieces; 
	std::vector <GameObject*> debugObject;
	GLuint myPiecesIndex ;

	int SphereId;
	//static int gameObjCount = 0;
	FileDataLoader* file;
	GameMediator* mediator ;
	MovementManager* movement;
	Collision* collision;
	float shVel;

	//Vector to store particle objects
	std::vector<ParticleEmitter*> particleObj;
};

#endif