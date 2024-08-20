
#include "mediator.h"


#include "sphere.h"
#include "Vector3D.h"
#include "basePhyComp.h"
#include "softBodyComp.h"
#include "havokPhyComp.h"
#include "havokPhantomComponent.h"
//Havok headers

// Keycode
#include <Common/Base/keycode.cxx>
#include <Common/Base/Config/hkProductFeatures.cxx>

// Math and base includes
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>

#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>

//Shapes
#include <Physics2012\Collide\Shape\Convex\Box\hkpBoxShape.h>
#include <Physics2012\Collide\Shape\Convex\Sphere\hkpSphereShape.h>
#include <Physics2012\Collide\Shape\HeightField\Plane\hkpPlaneShape.h>
#include <Physics2012\Collide\Shape\Convex\Triangle\hkpTriangleShape.h>
#include <Physics2012\Collide\Shape\Compound\Collection\List\hkpListShape.h>
#include <Physics2012\Collide\Shape\Compound\Tree\Mopp\hkpMoppCompilerInput.h>
#include <Physics2012\Collide\Shape\Compound\Tree\Mopp\hkpMoppUtility.h>
#include <Physics2012\Collide\Shape\Compound\Tree\Mopp\hkpMoppBvTreeShape.h>
#include <Physics2012\Utilities\Collide\ShapeUtils\MoppCodeStreamer\hkpMoppCodeStreamer.h>

//Constraint
#include <Physics\Constraint\Data\Hinge\hkpHingeConstraintData.h>
#include <Physics2012\Utilities\Dynamics\Inertia\hkpInertiaTensorComputer.h>
#include <Physics2012\Dynamics\World\hkpSimulationIsland.h>

// Havok Vehicle 

#include <Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Common/Internal/ConvexHull/hkGeometryUtility.h>
#include <Common/Base/Math/Matrix/hkMatrix3Util.h>

//Havok Phantom
#include <Physics2012/Dynamics/Phantom/hkpAabbPhantom.h>


#include "HavokVehicle.h"
#include "global.h"
#include <iostream>
#include <algorithm>
GameMediator::GameMediator()
{
	
}

GameMediator::~GameMediator()
{
	return;
}

GameObject* GameMediator::createObject(ObjectBox data)
{
	GameObject* newObject ;




	//Check type of object
	if (data.ObjectType == "SoftJelly")
	{
		newObject = new GameObject();
		newObject->setName(data.ObjectType);
		//newObject->setwireframe(true);
		newObject->setIsBlend(true);
		newObject->setBlendVal(1.5);
	}
	else if(data.ObjectType == "Skybox")
	{
		newObject = new SphereObj();
		newObject->setName(data.ObjectType);
		newObject->setIsSkyMap(true);
	}
	else
	{
		newObject = new GameObject();
		newObject->setName(data.ObjectType);
	}



	sceneList.push_back(newObject);
	newObject->attachMediator(this);
	newObject->shaderName = data.shaderName;
	return newObject;
}


void GameMediator::createModel(std::wstring fileName,std::string texture, std::string modelMode , std::string physics, std::string alText)
{
	bool isNew = true;
	//Model is same but color is different
	ModelData* data =  new ModelData();
	int bufferMode;
	if(physics == "softBody")
	{
		bufferMode = 0x88E0;   //gl Stream draw
	}
	else
	{
		bufferMode = 0x88E4;   //gl Static dRAW
	}

	//Object created now check if the model exists... (use filename and scale to compare)
	if(modelMode == "shared")
	{
		for(int i = 0 ; i < modelList.size(); i++)
		{
			if (modelList[i]->getFileName() == fileName ){
				//cool so that file is already added .



				data->setNumberOfElements(modelList[i]->GetNumberOfElements());
				data->setNumberOfVerticies(modelList[i]->GetNumberOfVerticies());

				data->setVerticies(modelList[i]->getVerticies());
				data->setElements(modelList[i]->getElements());
				data->calcualteExtents();

				data->setColor(Vector3D());
				data->setFileName(fileName);
				data->assignBuffer(bufferMode);

				//	newObject->setModelData(data);
				modelList.push_back(data);
				isNew = false;
				break;

			}
		}
	}
	if(isNew)
	{

		std::wstring error;
		if(data->OpenPLYFile(fileName,error))
		{
			data->setColor(Vector3D());
			//data->createBoxes();
			//data->populateBoxes();
			data->setFileName(fileName);
			data->assignBuffer(bufferMode);
			/*if(data->OpenBMPFile(texture, error)){
			data->setTextureName(texture);
			data->assignBuffer();
			}*/
		}

		//newObject->setModelData(data);


	}

	//Assign Texture Info 
	//Assign Texture Info 
	TextureData* text = textureList[texture];
	data->setTextureInfo(text->getTextureID(), text->getTextureCode(), text->getTextureNo());


	if(alText != "NULL")
	{

		int altTextureIndex = std::stoi(alText);
		data->setAltTexture(altTextureIndex);
	}
	else
	{
		std::cout<<"No alternate texture attached to the Model"<<std::endl;
	}



	modelList.push_back(data);
}
bool GameMediator::UpdateObjectPositionByID( Vector3D newPosition , GameObject* &object)
{
	// Found it
	// object->setPosition(newPosition);
	return true;
}

bool GameMediator::UpdateObjectRotationByID(  Vector3D newRotation , GameObject* &object )
{
	// Found it
	//  object->setRotation(newRotation);
	return true;
}

bool GameMediator::UpdateObjectScaleByID( float newScale , GameObject* &object )
{
	// Found it
	float extent = object->getMaxExtent();
	object->updatePhysicAttribute("SCALE",Vector3D(newScale,newScale,newScale));
	object->getModelData(0)->scaleVertices(newScale/ extent);

	//object->getModelData()->calcualteExtents();//drop this

	return true;
}

bool GameMediator::TestScale(float newScale, GameObject* &object)
{
	//	object->setScale(newScale);
	object->getModelData(0)->scaleVertices(newScale);
	return true;
}



bool GameMediator::UpdateObjectRadiusByID( float newRadius , GameObject* &object)
{
	((SphereObj*)object)->setRadius(newRadius);
	return true;
}

bool GameMediator::UpdateObjectVelocityByID( Vector3D newVelocity , GameObject* &object)
{
	// Found it
	//object->setVelocity(newVelocity);
	return true;
}

void GameMediator::createBoundingBox(GameObject* &value, std::vector <GameObject*> &debugList, std::string type, Vector3D offset) //2nd param list of debugobjects
{
	//ModelData* obj = value->getModelData();
	//
	//obj->createBoxes(type,offset);
	//obj->populateBoxes(offset);
	//
	////Fetch centre points and create cubes
	//std::vector<Vector3D> centres = obj->BBCenterVector();
	////for (int i = 0; i < centres.size(); i++)
	////{
	////	unsigned int ID = this->createObject("Cube", L"ply/Cube.ply", 3, debugList, "shared", "base");
	////	GameObject* cubeObj;
	////	bool IdFound = false;
	////	cubeObj = debugList.back();
	////	cubeObj->setwireframe(true);
	////	
	////	this->UpdateObjectPositionByID(centres[i], cubeObj);
	////	//this->UpdateObjectRotationByID(Vector3D(rotx, roty, rotz), obj);
	////	//mediator->UpdateObjectColourByID(Vector3D(colr,roty,rotz),obj);
	////	this->TestScale((5 * obj->getMaxExtent())/100, cubeObj);
	////}
}

//Loads Basic Texture and pushes it to list

TextureData* GameMediator::getTextureByName(std::string key)
{

	return this->textureList[key];
}




void GameMediator::createTextures(std::string textureType,std::string textureName)
{
	TextureData* textObj = new TextureData();
	std::wstring error;

	if(textObj->LoadBasicTexture(textureName, error))
	{
		textObj->setTextureName(textureType);				
	}


	//textureList.push_back(textObj);
	textureList[textureType]=textObj;
	TextureData::fixedindex = textureList.size();
}

void GameMediator::createSkybox(std::vector<std::string> textureName,std::string textureType)
{
	TextureData* textObj = new TextureData();
	std::wstring error;

	if(textObj->LoadSkyMapTexture(textureName, error))
	{
		textObj->setTextureName(textureType);				
	}
	//textureList.push_back(textObj);
	textureList[textureType]=textObj;
}

bool GameMediator::UpdateObjectAccelerationByID(  Vector3D newAcceleration ,   GameObject* &object)
{
	// Found it
	//	object->setAcceleration(newAcceleration);
	return true;
}

void GameMediator::setSphereId(int value)
{
	SphereId = value;

}

int GameMediator::getSphereId()
{
	return SphereId;
}

//...............Added In Project 3 ...............................

GLuint& GameMediator::getPlayerId(int index)
{
	return player_ids[index];
}

GLuint& GameMediator::getSkyBoxId()
{
	return skybox_id;
}

void GameMediator::setPlayerId(GLuint value)
{

	player_ids.push_back(value);
}

void GameMediator::setSkyBoxId(GLuint value)
{
	skybox_id = value;
}


//Not being used
void GameMediator::AttachPhysics(Vector3D position, Vector3D rotation,float scale, std::string phyType, std::string shape, GameObject* &object , softBodyAttribs s)
{
	IPhysicsComp* phys ;

	if(phyType == "softBody")
	{
		phys = new SoftBodyPhyComp();
		((SoftBodyPhyComp*)phys)->SetVertices(object->getModelData(0)->getVerticies(), 0.03f);
		((SoftBodyPhyComp*)phys)->ComputeSprings(object->getModelData(0)->getElements(), s.indexOffset);

		//object->setwireframe(true);

		for(int i = 0 ; i < s.fixedNodes.size(); i++)
		{
			((SoftBodyPhyComp*)phys)->SetNodeFixed(s.fixedNodes[i],true);
		}


		((SoftBodyPhyComp*)phys)->SetSpringConst(s.springConst);
	}
	else
	{
		phys = new BasePhyComp();
		((BasePhyComp*)phys)->shape = shape;
	}

	if(phyType == "disabled")
	{
		((BasePhyComp*)phys)->physicsEnabled = false;
	}

	glm::quat r;
	phys->RegisterPhyAttributes(position, r, scale);

	if(shape == "sphere")
	{
		((BasePhyComp*)phys)->radius = 0.5f;
	}
	else if(shape == "cube")
	{
		ModelData* data = object->getModelData(0);
		((BasePhyComp*)phys)->min = Vector3D(data->getMinX(), data->getMinY(), data->getMinZ());
		((BasePhyComp*)phys)->max = Vector3D(data->getMaxX(), data->getMaxY(), data->getMaxZ());

	}

	object->attachPhysics(phys);
	((BasePhyComp*)phys)->mediator = this;

	physicComp.push_back(phys);

}

bool GameMediator::UpdateObjectAttribVector(std::string type, Vector3D value,  GameObject* &object)
{
	object->updatePhysicAttribute(type, value);
	return true;
}

std::vector<IPhysicsComp*> GameMediator::fetchPhyComp()
{
	return physicComp;
}

std::vector<ModelData*> GameMediator::fetchModelComp()
{
	return modelList;
}

//.................................Havok................................................

void GameMediator::initHavok()
{
	this->mVDBEnabled = true;
	InitMemory();
	InitWorld();
	if (mVDBEnabled)
	{
		InitVDB();
	}
}

void GameMediator::shutdown()
{
	// Cleanup physics
	mWorld->markForWrite();
	mWorld->removeReference();
	mWorld = HK_NULL;

	delete mJobQueue;

	// Clean up the thread pool
	mThreadPool->removeReference();

	if (mVDBEnabled)
	{
		mVisualDebugger->removeReference();
		// Contexts are not reference counted at the base class level by the VDB as
		// they are just interfaces really. So only delete the context after you have
		// finished using the VDB.
		mPhysicsContext->removeReference();
	}

	hkBaseSystem::quit();
	hkMemoryInitUtil::quit();
}

void OnError(const char* msg, void* userArgGivenToInit)
{
	std::cerr << "Report: " << msg << std::endl; 
}

void GameMediator::InitMemory()
{
#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
	// Flush all denormal/subnormal numbers (2^-1074 to 2^-1022) to zero.
	// Typically operations on denormals are very slow, up to 100 times slower than normal numbers.
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif 

	// Initialize the base system including our memory system
	// Allocate 0.5MB of physics solver buffer.
	hkMemoryAllocator* baseMalloc = hkMallocAllocator::m_defaultMallocAllocator;
	hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault(baseMalloc, hkMemorySystem::FrameInfo( 500* 1024 ) );

	hkBaseSystem::init( memoryRouter, OnError );


	// We can cap the number of threads used - here we use the maximum for whatever multithreaded platform we are running on. This variable is
	// set in the following code sections.
	int totalNumThreadsUsed;

	// Get the number of physical threads available on the system
	hkHardwareInfo hwInfo;
	hkGetHardwareInfo(hwInfo);
	totalNumThreadsUsed = hwInfo.m_numThreads;

	// We use one less than this for our thread pool, because we must also use this thread for our simulation
	hkCpuJobThreadPoolCinfo threadPoolCinfo;
	threadPoolCinfo.m_numThreads = totalNumThreadsUsed - 1;

	// This line enables timers collection, by allocating 200 Kb per thread.  If you leave this at its default (0),
	// timer collection will not be enabled.
	threadPoolCinfo.m_timerBufferPerThreadAllocation = 200000;
	mThreadPool = new hkCpuJobThreadPool( threadPoolCinfo );

	// We also need to create a Job queue. This job queue will be used by all Havok modules to run multithreaded work.
	// Here we only use it for physics.
	hkJobQueueCinfo info;
	info.m_jobQueueHwSetup.m_numCpuThreads = totalNumThreadsUsed;
	mJobQueue = new hkJobQueue(info);

	// Enable monitors for this thread.
	// Monitors have been enabled for thread pool threads already (see above comment).
	hkMonitorStream::getInstance().resize(200000);
}

void GameMediator::InitWorld()
{
	// Set the simulation type of the world to multi-threaded.
	//mWorldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_MULTITHREADED;
	mWorldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_DISCRETE;
	mWorldInfo.m_fireCollisionCallbacks =true;//  hkpWorldCinfo::m_fireCollisionCallbacks
	mWorldInfo.m_gravity = hkVector4(0.0f,-7.0f,0.0f,1.0f);
	// Flag objects that fall "out of the world" to be automatically removed.
	mWorldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_REMOVE_ENTITY;

	mWorld = new hkpWorld(mWorldInfo);

	// Disable deactivation, so that you can view timers in the VDB. This should not be done in your game.
	mWorld->m_wantDeactivation = false;

	// When the simulation type is SIMULATION_TYPE_MULTITHREADED, in the debug build, the sdk performs checks
	// to make sure only one thread is modifying the world at once to prevent multithreaded bugs. Each thread
	// must call markForRead / markForWrite before it modifies the world to enable these checks.
	mWorld->markForWrite();


	// Register all collision agents.
	// It's important to register collision agents before adding any entities to the world.
	hkpAgentRegisterUtil::registerAllAgents( mWorld->getCollisionDispatcher() );

	// We need to register all modules we will be running multi-threaded with the job queue.
	mWorld->registerWithJobQueue( mJobQueue );
}

void GameMediator::InitVDB()
{
	hkArray<hkProcessContext*> contexts;

	// <PHYSICS-ONLY>: Register physics specific visual debugger processes
	// By default the VDB will show debug points and lines, however some products such as physics and cloth have additional viewers
	// that can show geometries etc and can be enabled and disabled by the VDB app.
	{
		// Initialise the visual debugger so we can connect remotely to the simulation.
		// The context must exist beyond the use of the VDB instance, and you can make
		// whatever contexts you like for your own viewer types.
		mPhysicsContext = new hkpPhysicsContext();
		hkpPhysicsContext::registerAllPhysicsProcesses(); // all the physics viewers
		mPhysicsContext->addWorld(mWorld); // add the physics world so the viewers can see it
		contexts.pushBack(mPhysicsContext);

		// Now we have finished modifying the world, release our write marker.
		mWorld->unmarkForWrite();
	}

	mVisualDebugger = new hkVisualDebugger(contexts);
	mVisualDebugger->serve();
}

void GameMediator::StepHavok( hkReal timeStep )//not being used.......3/19/2015
{
	//mWorld->stepMultithreaded( mJobQueue, mThreadPool, timeStep);
	mWorld->stepDeltaTime(timeStep);

	if(mVDBEnabled)
	{
		mPhysicsContext->syncTimers(mThreadPool);
		mVisualDebugger->step(timeStep);
	}

	// Clear accumulated timer data in this thread and all slave threads
	hkMonitorStream::getInstance().reset();
	mThreadPool->clearTimerData();
}

void GameMediator::Update( float dt )
{
	//mWorld->markForRead();
	//mWorld->stepMultithreaded( mJobQueue, mThreadPool, 0.01f);
	mWorld->stepDeltaTime(0.01f);
	if(mVDBEnabled)
	{
		mPhysicsContext->syncTimers(mThreadPool);
		mVisualDebugger->step(0.01f);
	}

	// Clear accumulated timer data in this thread and all slave threads
	hkMonitorStream::getInstance().reset();
	mThreadPool->clearTimerData();

	for(int i = 0 ; i < physicComp.size(); i++)
	{
		if(physicComp[i]->getType() == "HAVOK")
		{
			if(!((HavokPhyComp*)physicComp[i])->isAlive())
			{
				mWorld->lock();
				cHavokRigidBody* newBody = ((HavokPhyComp*)physicComp[i])->GetBody();

				//	newBody->mInfo.m_position = hkVector4(0.0f, 3.0f,0.0f,1.0f);

				hkpRigidBody* nHKBody = new hkpRigidBody(newBody->mInfo);

				mWorld->addEntity(nHKBody);
				newBody->pHKBody = nHKBody;
				nHKBody->addEntityListener(&(((HavokPhyComp*)physicComp[i])->mEntityListener));
				nHKBody->addContactListener(&(((HavokPhyComp*)physicComp[i])->mCollisionListener));
				mWorld->unlock();

				((HavokPhyComp*)physicComp[i])->setAlive();
			}
		}
	}


	std::vector<Vector3D> wheelTracks;
	//To update Wheels 
	for(int i = 0 ; i < sceneList.size() ; i++)
	{
		if(sceneList[i]->getName() == "Vehicle")
		{
			mWorld->lock();
			sceneList[i]->updateWheels(wheelTracks);
			mWorld->unlock();
		}


	}



	//Particle 
	for(int i = 0 ; i < wheelTracks.size(); i++ )
	{
		//std::cout<<"Wheel track "<<wheelTracks[i].x<<" "<<wheelTracks[i].y<<" "<<wheelTracks[i].z<<std::endl;
		this->genParticles(wheelTracks[i]);
	}
	

	for(int i = 0 ; i < particleObj.size(); i++)
	{
         particleObj[i]->Update( dt );


	     std::vector< ParticleEmitter::CParticle > vecParticles;
	     particleObj[i]->GetParticles(vecParticles);
	
	     for ( int index = 0; index != vecParticles.size(); index++ )
	     {
		     createParticles(vecParticles[index].position);
	
	     }


	     if(!particleObj[i]->Alive())
	     {
			 

			 std::vector<ParticleEmitter*>::iterator newEnd = std::remove(particleObj.begin(), particleObj.end(), particleObj[i]);
			 //Erase the "removed" elements.
            particleObj.erase(newEnd, particleObj.end());
	      }


	}


	//	mWorld->unmarkForRead();
}

void GameMediator::RenderingBegin()
{
	mWorld->markForRead();
}

void GameMediator::RenderingEnd()
{
	mWorld->unmarkForRead();
}

void GameMediator::Lock()
{
	mWorld->lock();
}

void GameMediator::Unlock()
{
	mWorld->unlock();
}

hkpConvexVerticesShape* GameMediator::createChassisShape()
{

	hkReal xSize = 0.75f;
	hkReal ySize = 0.25f;
	hkReal zSize = 0.1f;

	hkReal xBumper = 1.9f;
	hkReal yBumper = 0.15f;
	hkReal zBumper = 1.0f;

	hkReal xRoofFront = 0.4f;
	hkReal xRoofBack = -1.0f;
	hkReal yRoof = ySize + 0.45f;
	hkReal zRoof = 0.7f;

	hkReal xDoorFront = xRoofFront;
	hkReal xDoorBack = xRoofBack;
	hkReal yDoor = ySize;
	hkReal zDoor = zSize + 0.1f;

	int numVertices = 22;

	int stride = sizeof(hkReal) * 4;

	HK_ALIGN_REAL(hkReal vertices[] )= { 
		xSize, ySize, zSize, 0.0f,		// v0
		xSize, ySize, -zSize, 0.0f,		// v1
		xSize, -ySize, zSize, 0.0f,		// v2
		xSize, -ySize, -zSize, 0.0f,	// v3
		-xSize, -ySize, zSize, 0.0f,	// v4
		-xSize, -ySize, -zSize, 0.0f,	// v5

		xBumper, yBumper, zBumper, 0.0f,	// v6
		xBumper, yBumper, -zBumper, 0.0f,	// v7
		-xBumper, yBumper, zBumper, 0.0f,	// v8
		-xBumper, yBumper, -zBumper, 0.0f,	// v9

		xRoofFront, yRoof, zRoof, 0.0f,		// v10
		xRoofFront, yRoof, -zRoof, 0.0f,	// v11
		xRoofBack, yRoof, zRoof, 0.0f,		// v12
		xRoofBack, yRoof, -zRoof, 0.0f,		// v13

		xDoorFront, yDoor, zDoor, 0.0f,		// v14
		xDoorFront, yDoor, -zDoor, 0.0f,	// v15
		xDoorFront, -yDoor, zDoor, 0.0f,	// v16
		xDoorFront, -yDoor, -zDoor, 0.0f,	// v17

		xDoorBack, yDoor, zDoor, 0.0f,		// v18
		xDoorBack, yDoor, -zDoor, 0.0f,		// v19
		xDoorBack, -yDoor, zDoor, 0.0f,		// v20
		xDoorBack, -yDoor, -zDoor, 0.0f,	// v21
	};

	//
	// SHAPE CONSTRUCTION.
	//

	hkStridedVertices		stridedVerts;
	stridedVerts.m_numVertices	=	numVertices;
	stridedVerts.m_striding		=	stride;
	stridedVerts.m_vertices		=	vertices;

	return new hkpConvexVerticesShape(stridedVerts);


}


hkpConvexVerticesShape* GameMediator::createChassisShape(ModelData* data )
{

	Vector3D max = Vector3D(data->getMaxX(), data->getMaxY(), data->getMaxZ()) ;
	Vector3D min =  Vector3D(data->getMinX(), data->getMinY(), data->getMinZ());


	hkReal xSize = 0.75f;
	hkReal ySize = 0.25f;
	hkReal zSize = 0.1f;

	hkReal xBumper = 1.9f;
	hkReal yBumper = 0.15f;
	hkReal zBumper = 1.0f;

	hkReal xRoofFront = 0.4f;
	hkReal xRoofBack = -1.0f;
	hkReal yRoof = ySize + 0.45f;
	hkReal zRoof = 0.7f;

	hkReal xDoorFront = xRoofFront;
	hkReal xDoorBack = xRoofBack;
	hkReal yDoor = ySize;
	hkReal zDoor = zSize + 0.1f;

	int numVertices = 8;

	int stride = sizeof(hkReal) * 4;

	HK_ALIGN_REAL(hkReal vertices[] )= { 
		min.x, min.y , min.z , 0.0f, 
		min.x, min.y, max.z, 0.0f ,
		min.x, max.y , min.z , 0.0f,
		min.x, max.y, max.z, 0.0f,
		max.x, min.y , min.z , 0.0f, 
		max.x, min.y, max.z, 0.0f ,
		max.x, max.y , min.z , 0.0f,
		max.x, max.y, max.z, 0.0f,

	};

	//
	// SHAPE CONSTRUCTION.
	//

	hkStridedVertices		stridedVerts;
	stridedVerts.m_numVertices	=	numVertices;
	stridedVerts.m_striding		=	stride;
	stridedVerts.m_vertices		=	vertices;

	return new hkpConvexVerticesShape(stridedVerts);


}
void GameMediator::AttachPhysics( GameObject* &object, softBodyAttribs a , cHavokBodyDesc &r, int index)
{
	hkpRigidBodyCinfo info;
	hkpShape* havokShape = 0;


	if(r.enabled)
	{
		if (r.IsStatic) 
		{
			info.m_motionType = hkpMotion::MOTION_FIXED;
		}
		else
		{
			info.m_motionType = hkpMotion::MOTION_DYNAMIC;
		}


		info.m_position.set(r.Position.x, r.Position.y, r.Position.z);
		info.m_rotation.set(r.Rotation.x, r.Rotation.y, r.Rotation.z, r.Rotation.w);
		info.m_linearVelocity.set(r.LinearVelocity.x, r.LinearVelocity.y, r.LinearVelocity.z);
		info.m_angularVelocity.set(r.AngularVelocity.x, r.AngularVelocity.y, r.AngularVelocity.z);
		info.m_maxLinearVelocity = r.MaxLinearVelocity;
		info.m_maxAngularVelocity = r.MaxAngularVelocity;
		info.m_linearDamping = r.LinearDamping;
		info.m_angularDamping = r.AngularDamping;
		info.m_mass = r.Mass;
		info.m_restitution = r.Restitution;
		info.m_friction = r.Friction;

		bool needsMassProperties = false;

		switch (r.shape)
		{
		case BOX:
			{
				ModelData* data = object->getModelData(index);

				Vector3D max = Vector3D(data->getMaxX(), data->getMaxY(), data->getMaxZ()) ;
				Vector3D min =  Vector3D(data->getMinX(), data->getMinY(), data->getMinZ());

				Vector3D halfWidth = (max - min)/2.2; 
				havokShape = new hkpBoxShape(GetHKV4(halfWidth));
				needsMassProperties = true;

				if (needsMassProperties)
				{
					hkMassProperties massProps;
					hkpInertiaTensorComputer::computeShapeVolumeMassProperties(havokShape, info.m_mass, massProps);
					info.setMassProperties(massProps);
				}

				info.m_shape = havokShape;
			}
			break;
		case SPHERE:
			{
				ModelData* data = object->getModelData(index);

				Vector3D max = Vector3D(data->getMaxX(), data->getMaxY(), data->getMaxZ()) ;
				Vector3D min =  Vector3D(data->getMinX(), data->getMinY(), data->getMinZ());


				havokShape = new hkpSphereShape((max.x - min.x)/2);
				needsMassProperties = true;

				if (needsMassProperties)

				{
					hkMassProperties massProps;
					hkpInertiaTensorComputer::computeShapeVolumeMassProperties(havokShape, info.m_mass, massProps);
					info.setMassProperties(massProps);

				}

				info.m_shape = havokShape;

			}
			break;

		case PLANE:
			{
				ModelData* data = object->getModelData(index);

				Vector3D max = Vector3D(data->getMaxX(), data->getMaxY(), data->getMaxZ()) ;
				Vector3D min =  Vector3D(data->getMinX(), data->getMinY(), data->getMinZ());

				Vector3D halfWidth = (max - min)/2; 

				std::vector<PLYVERTEX> m_verticies = data->getVerticies();
				std::vector<PLYELEMENT> m_elements = data->getElements();



				Vector3D vertex_1 = (data->getVerticies())[(m_elements[0]).vertex_1].pos;
				Vector3D vertex_2 = (data->getVerticies())[(m_elements[0]).vertex_2].pos;
				Vector3D vertex_3 = (data->getVerticies())[(m_elements[0]).vertex_3].pos;


				Vector3D normal = Vector3D::CrossProduct(vertex_2 - vertex_1, vertex_3 - vertex_1); 
				Vector3D::Normalize(normal);
				havokShape = new hkpPlaneShape(GetHKV4(normal), info.m_position, GetHKV4(halfWidth));


				if (needsMassProperties)	
				{
					hkMassProperties massProps;
					hkpInertiaTensorComputer::computeShapeVolumeMassProperties(havokShape, info.m_mass, massProps);
					info.setMassProperties(massProps);

				}

				info.m_shape = havokShape;
			}

			break;

		case COMPLEX:
			{
				ModelData* data = object->getModelData(index);
				hkArray<hkpShape*> shapeArray;
				std::vector<PLYVERTEX> m_verticies = data->getVerticies();
				std::vector<PLYELEMENT> m_elements = data->getElements();

				for(int i = 0 ; i < m_elements.size(); i++)
				{
					hkVector4 vertex1((m_verticies[m_elements[i].vertex_1]).pos.x, (m_verticies[m_elements[i].vertex_1]).pos.y ,(m_verticies[m_elements[i].vertex_1]).pos.z, 1.0f);
					hkVector4 vertex2((m_verticies[m_elements[i].vertex_2]).pos.x, (m_verticies[m_elements[i].vertex_2]).pos.y ,(m_verticies[m_elements[i].vertex_2]).pos.z, 1.0f);
					hkVector4 vertex3((m_verticies[m_elements[i].vertex_3]).pos.x, (m_verticies[m_elements[i].vertex_3]).pos.y ,(m_verticies[m_elements[i].vertex_3]).pos.z, 1.0f);

					havokShape = new hkpTriangleShape(vertex1,vertex2,vertex3);

					shapeArray.pushBack(havokShape);
				}

				/////////////////// SHAPE CONSTRUCTION ////////////////
				hkpListShape* listShape = new hkpListShape(shapeArray.begin(), shapeArray.getSize());

				// Remove reference since the listShape now "owns" the boxShapes.
				for(int i = 0 ; i < shapeArray.getSize();i++)
				{
					shapeArray[i]->removeReference();
				}

				hkpMoppCompilerInput moppInput;
				moppInput.setAbsoluteFitToleranceOfTriangles(0.1f);
				hkpMoppCode* code = hkpMoppUtility::buildCode(listShape, moppInput);

				hkpMoppBvTreeShape* shape = new hkpMoppBvTreeShape(listShape, code);

				// Remove references since the MoppBvTreeShape now "owns" the listShape and code
				code->removeReference();
				listShape->removeReference();

				info.m_shape = shape;

			}
			break;

		case CHASSIS:
			{
				ModelData* data = object->getModelData(index);

				havokShape = createChassisShape(data);


				info.m_mass = 750.0f;
				info.m_friction = 0.8;

				hkMatrix3Util::_setDiagonal(1.0f,1.0f,1.0f,info.m_inertiaTensor);
				info.m_centerOfMass.set(0.0f,0.5f,0.0f);
				info.m_shape =  havokShape;
				info.m_motionType  = hkpMotion::MOTION_BOX_INERTIA;
			}
			break;

		default:

			{
				std::cout<<"Invalid shape"<<std::endl;
			}
		}
		//------------------------------------------------------
		hkpRigidBody* body = new hkpRigidBody(info);

		if(r.shape == CHASSIS)
		{
			//----HAvokVehicle----------made after the rigid body is set??
			hkpVehicleInstance* vehicleInstance = new hkpVehicleInstance(body);
			
			
			

			VehicleSetup vehicleObj;

			vehicleObj.buildVehicle(mWorld,*vehicleInstance);


			//	
			//-----------example implementation--------------------
			vehicleInstance->m_data->m_chassisOrientation.setCols( hkVector4(0, 1, 0), hkVector4(1, 0, 0), hkVector4(0, 0, 1));
			//----------------------------------------
			vehicleInstance->init();// Inti the HkpVehicleINstance after all values and parameters are set


			vehicleInstance->addToWorld(mWorld); //we are already including the vehicle obj  in the Hkworld
			mWorld->addAction(vehicleInstance);

			//	vehicleInstance->getChassis()->activate();
			object->m_vehicleInstance = vehicleInstance;



			object->playerId = body->getUid();

			////set player in Game Manager
			if(gameManager->player1.id != -1)
			{
				gameManager->player1.id = body->getUid();
			
			}
			else
			{
				gameManager->player2.id = body->getUid();
			
			}
			//--------------------------

		}
		else
		{
			mWorld->addEntity(body);
		}		//----------------------------------

		//mWorld->addEntity(body);

		havokShape->removeReference();

		cHavokRigidBody* mBody = new cHavokRigidBody(body);
		mBody->mInfo = info;
		HavokPhyComp* phyComp = new HavokPhyComp(mBody);


		// //check for constraint
		// if(r.constraintEnabled)
		// {
		////
		//// CREATE HINGE CONSTRAINT
		////
		////Get previous body
		//	 GameObject* otherObject = new GameObject();
		//
		//			 for(int k = 0 ; k < sceneList.size() ; k++)
		//			 {
		//				 if(sceneList[k]->getName() == "Cube1")  //Cube1 will be passed from xml later
		//				 {
		//					otherObject = sceneList[k];
		//					break;
		//				 }
		//			 }
		//
		//	 HavokPhyComp* otherPhyBody = (HavokPhyComp*)otherObject->getPhyComp();
		//	 hkpRigidBody* otherBody = (otherPhyBody->GetBody()->pHKBody);
		//
		//hkpHingeConstraintData* hc = new hkpHingeConstraintData();
		//
		//	ModelData* data = object->getModelData();
		//
		//		Vector3D max = Vector3D(data->getMaxX(), data->getMaxY(), data->getMaxZ()) ;
		//
		//		// Set the pivot
		//	hkVector4 pivot(max.x,max.y,max.z);		
		//	//pivot.setAdd4(position, halfSize);
		//
		//	//// Move pivot to center of side on cube
		//	//pivot(0) -= size(0);
		//	//pivot(2) -= halfSize(2);
		//
		//	hkVector4 axis(0.0f, 0.0f, 1.0f);
		//
		//		// Create constraint
		//	hc->setInWorldSpace(body->getTransform(), otherBody->getTransform(), pivot, axis);		
		//	hc->setSolvingMethod( hkpConstraintAtom::METHOD_STABILIZED );
		//	//
		//	hkpConstraintInstance* constraint = new hkpConstraintInstance(body, otherBody, hc);
		//	mWorld->addConstraint( constraint); 
		//	constraint->removeReference();
		//
		//	hc->removeReference();
		// }

		object->attachPhysics(phyComp);
		this->physicComp.push_back(phyComp);

	}
	else
	{
		BasePhyComp* phyComp = new BasePhyComp();
		phyComp->physicsEnabled = false;
		glm::quat rot;
		phyComp->RegisterPhyAttributes(r.Position ,rot, r.scale);
		object->attachPhysics(phyComp);
		this->physicComp.push_back(phyComp);
	}
}


void GameMediator::AttachPhantom(GameObject* &object, softBodyAttribs a , cHavokBodyDesc &r, int index)
{


	hkAabb info;
	info.m_min = hkVector4( r.minExtent.x + r.Position.x, r.minExtent.y  + r.Position.y, r.minExtent.z  + r.Position.z );
	info.m_max = hkVector4( r.maxExtent.x  + r.Position.x, r.maxExtent.y  + r.Position.y, r.maxExtent.z  + r.Position.z) ;
	
	hkpAabbPhantom* m_phantom = new hkpAabbPhantom( info );
	IPhysicsComp* myphantom = new HavokPhantomComp(m_phantom);
	if(object->getName().find("checkpoint") ==  std::string::npos)
	{
		BasePhyComp* phyComp = new BasePhyComp();
		phyComp->physicsEnabled = false;
		glm::quat rot;
		phyComp->RegisterPhyAttributes(r.Position ,rot, 1.0f);
		object->attachPhysics(phyComp);
		this->physicComp.push_back(phyComp);
		((HavokPhantomComp*)myphantom)->TYPE = POWERUP;
		
	}else
	{
		((HavokPhantomComp*)myphantom)->TYPE = CHECKPOINT;
		std::string name = object->getName();
		int index = std::stoi(name.substr(name.size()-1,name.size()));
		((HavokPhantomComp*)myphantom)->index = index;
		std::cout<<"Checkpoint index "<<index<<std::endl;
	}
	

	
	((HavokPhantomComp*)myphantom)->parentMediator = this;
	
	((HavokPhantomComp*)myphantom)->parentObject = object;
	object->attachPhysics(myphantom);
	this->physicComp.push_back(myphantom);


	mWorld->addPhantom(m_phantom);

}


//TextureData* GameMediator::fetchTextureAtIndex(int index)
//{
//	return textureList[index];
//}

std::vector<GameObject*> GameMediator::fetchSceneList()
{
	return sceneList;
}


void GameMediator::mediatorUserInput(ButtonPressed input, int index)
{
	GameObject* obj = sceneList[0];
	bool IdFound = false;
	for(int i = 0 ; i < this->sceneList.size(); i ++)
	{
		if(this->sceneList[i]->getID() == this->player_ids[index]){
			obj = this->sceneList[i];
			IdFound = true;
		}
	}

	if(IdFound)
	{
		obj->processUserInput(input);
	}

}




void GameMediator::createShader(ShaderBox data)
{
	std::cout<<"Loading Shader "<<data.shaderName<<std::endl;
	Shader* myShader = new Shader(data.shaderName);

	for(std::map<GLenum, std::string>::iterator mapIter = data.components.begin(); mapIter != data.components.end(); mapIter++)
	{
		myShader->addShader(mapIter->first, mapIter->second);
	}

	myShader->linkShader();

	myShader->addUniformVariables(data.uniformVarType);

	this->shaderStore[data.shaderName] = myShader;

}

//To fetch Shaders
std::map<std::string , Shader*> GameMediator::fetchShaders()
{
	return shaderStore;
}



void GameMediator::createParticles(Vector3D origin)
{
	GameObject* newObject  = new GameObject();
	newObject->setName("particle");
	newObject->shaderName = "simple";
	bool found = false;
	for(int i = 0 ; i < modelList.size(); i++)
	{
		if (modelList[i]->getFileName() == L"ply/Cube.ply")
		{
			//newObject->setModelData(modelList[i]);
			newObject->attachModelData(modelList[i]);
			found = true;
		}



	}

	if(!found)
	{

		ModelData* ModData = new ModelData();
		std::wstring error;
		if(ModData->OpenPLYFile(L"ply/Cube.ply",error))
		{

			//data->createBoxes();
			//data->populateBoxes();
			ModData->setFileName(L"ply/Cube.ply");
			ModData->assignBuffer(0x88E4);
			/*if(data->OpenBMPFile(texture, error)){
			data->setTextureName(texture);
			data->assignBuffer();
			}*/
		}

		newObject->attachModelData(ModData);

		TextureData* text = textureList["wall"];
		ModData->setTextureInfo(text->getTextureID(), text->getTextureCode(), text->getTextureNo());


		modelList.push_back(ModData);

	}


}


std::vector<GameObject*> GameMediator::fetchParticleList()
{
	return particleList;
}


void GameMediator::genParticles(Vector3D origin)
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