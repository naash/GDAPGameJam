#include "delegator.h"
#include <sstream>
#include <algorithm>

Delegator::Delegator()
{
	mediator = new GameMediator();
	movement = new MovementManager();
	file = new FileDataLoader();
	collision = new Collision();

	shVel = 0.0f;
	myPiecesIndex = 0;
		
}

Delegator::~Delegator()
{

}

//To create entire scene
void Delegator::createScene(CShaderUniformVariables &g_ShaderUniformVariables , int index)
{
	mediator->initHavok();

	mediator->Lock();
	if(index == 1)
	{
		file->loadXML("external_file/scene1.xml","Scene",mediator , g_ShaderUniformVariables);
	}
	else
	{
		file->loadXML("external_file/scene2.xml","Scene",mediator , g_ShaderUniformVariables);
	}
	

	mediator->Unlock();
}


//Fetch list of player objects
	std::vector <GLuint> Delegator::getMyPieces()
	{
		return myPieces;
	}


	//To create Game Objects
unsigned int Delegator::createObject(std::string ObjectType, std::string fileName ,int textureName, std::string modelMode)
{
	//unsigned int id = mediator->createObject(ObjectType,ASCII_to_Unicode(fileName),textureName, modelMode, "base");
    return 1;
}

void Delegator::simulation(float deltaTime)
{
	//Sub at 1 index and Cave at index 2 
	bool collided = false;
	Vector3D origin;
	//collision->CollisionCheckForSub(sceneList, 1 , collided, origin);

    
	//Havok Update
	mediator->Update(deltaTime);
	
}


void Delegator::updateObject(std::string UpdateType, Vector3D vecAttrib,unsigned int ID, float param)
{
	//Find that object
	GameObject* obj ;
	bool IdFound = false;
	for(int i = 0 ; i < mediator->fetchSceneList().size(); i ++)
	{
		if(mediator->fetchSceneList()[i]->getID() == ID){
			obj = mediator->fetchSceneList()[i];
			IdFound = true;
		}
	}

 if(IdFound)
	{
	/*if(UpdateType == "POSITION")
	{
		mediator->UpdateObjectPositionByID(vecAttrib,obj );
	}
	else if(UpdateType == "ROTATION")
	{
		mediator->UpdateObjectRotationByID(vecAttrib,obj);
	}
	else if(UpdateType == "VELOCITY")
	{
		mediator->UpdateObjectVelocityByID(vecAttrib,obj);
	
	}
	else if(UpdateType == "ACCELERATION")
	{
		mediator->UpdateObjectAccelerationByID(vecAttrib,obj);
	
	}
	else if(UpdateType == "SCALE")
	{
		mediator->UpdateObjectScaleByID(param, obj);
	}else if(UpdateType == "COLOUR")
	{
		
		mediator->UpdateModelColourByID(vecAttrib, obj);
	}*/
		mediator->UpdateObjectAttribVector(UpdateType, vecAttrib, obj);
	}
	
}





//Fetch list of game objects created.
std::vector <GameObject*> Delegator::getSceneList()
{
	return mediator->fetchSceneList();
}


// NOTE: There are WAY better (i.e. safer!) ways to do this. See MultiByteToWideChar(), etc. in windows
// But this is "good enough" for now
std::wstring Delegator::ASCII_to_Unicode( std::string ASCIIstring )
{
	std::wstringstream ssReturnUNICODE;
	for ( std::string::iterator itChar = ASCIIstring.begin(); itChar != ASCIIstring.end(); itChar++ )
	{
		wchar_t theChar = static_cast<wchar_t>( *itChar );
		ssReturnUNICODE << theChar;
	}
	return ssReturnUNICODE.str();
}


//Fetch player id 
GLuint Delegator::getPlayerId(int index)
	{
		return mediator->getPlayerId(index);
	}

GLuint Delegator::getSkyBoxId()
	{
		return mediator->getSkyBoxId();
	}

int Delegator::getSphereId()
	{
		return mediator->getSphereId();
	}
	//Fetch List index
GLuint Delegator::getMyPiecesIndex()
	{
		return myPiecesIndex;
	}

void Delegator::setMyPiecesIndex(GLuint value)
	{
		myPiecesIndex =value;
	}

std::vector <GameObject*> Delegator::getDebugObject()

	{
		return debugObject;
	}


void Delegator::genParticles(Vector3D origin)
	{
		ParticleEmitter* part = new ParticleEmitter();
		part->SetLocation( origin );
		

		part->GenerateParticles( 25,Vector3D( 0.5f, 1.1f, 0.5f ),
			 /*dist from source */         0.0f, 
			                                2.0f, /*seconds*/
											false);
		part->SetAcceleration( Vector3D( 0.0f, 0.1f, 0.0f ) );
	
		particleObj.push_back(part);
	
	}

std::vector <GameObject*> Delegator::getParticleList()
	{
		return particleList;
	}


void Delegator::loadTextures()
	{
		file->loadTexture(mediator);
	}



void Delegator::loadSkyBox(std::vector<std::string> textureName,std::string textureType)
	{
		mediator->createSkybox(textureName,textureType);
	}

Vector3D Delegator::getSkyboxPos()
	{
		//Find player pos
		GameObject* obj = new GameObject();
		bool IdFound = false;
		for (int i = 0; i < mediator->fetchSceneList().size(); i++)
		{
			if (mediator->fetchSceneList()[i]->getID() == mediator->getSkyBoxId())
			{
				obj = mediator->fetchSceneList()[i];
				IdFound = true;
				break;
			}
		}
		
		Vector3D skyboxPos;// = obj->getPosition();

		return skyboxPos;
	}



Vector3D Delegator::getPlayerPos(int index)
	{
		//Find player pos
		GameObject* obj = new GameObject();
		bool IdFound = false;
		for (int i = 0; i < mediator->fetchSceneList().size(); i++)
		{
			if (mediator->fetchSceneList()[i]->getID() == mediator->getPlayerId(index)){
				obj = mediator->fetchSceneList()[i];
				IdFound = true;
				break;
			}
		}
		Vector3D playerPos = obj->getPhysicAttribute("POSITION") ;

		return playerPos;
	}

void Delegator::setTextureMixVal(std::string ObjectType,float value)
	{
		GameObject* objTextValChange = new GameObject();
		for (int i = 0; i < mediator->fetchSceneList().size(); i++)
		{
			if (mediator->fetchSceneList()[i]->getName() == ObjectType)
			{
				objTextValChange = mediator->fetchSceneList()[i];
				objTextValChange->setTextureMix(value);
			}
		}

	}

void Delegator::setBlendVal(std::string ObjectType, float value)
	{
		GameObject* objTextValChange = new GameObject();
		for (int i = 0; i < mediator->fetchSceneList().size(); i++)
		{
			if (mediator->fetchSceneList()[i]->getName() == ObjectType)
			{
				objTextValChange = mediator->fetchSceneList()[i];
				objTextValChange->setBlendVal(value);
			}
		}

	}


void Delegator::callFunc(std::string type)
	{
	 if(type == "RENDER")
	 {
		 mediator->RenderingBegin();
	 }
	 else if(type == "ENDRENDER")
	 {
		 mediator->RenderingEnd();
	 }
	}

void Delegator::userInput(ButtonPressed input,  int index)
{
	this->mediator->mediatorUserInput(input, index);

}

	//To fetch Shaders
	std::map<std::string , Shader*> Delegator::getShaders()
	{
		return mediator->fetchShaders();
	}

	TextureData* Delegator::getTexture(std::string name)
	{
	
		return mediator->getTextureByName(name);
	}

		Vector3D Delegator::getPlayerRotation(int index)
	{
		GameObject* obj = new GameObject();
		bool IdFound = false;
		for (int i = 0; i < mediator->fetchSceneList().size(); i++)
		{
			if (mediator->fetchSceneList()[i]->getID() == mediator->getPlayerId(index)){
				obj = mediator->fetchSceneList()[i];
				IdFound = true;
				break;
			}
		}
		Vector3D playerPos = obj->getPhysicAttribute("ROTATION") ;
		return playerPos;
	}