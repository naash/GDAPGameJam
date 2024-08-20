#ifndef _IFactory_HG_
#define _IFactory_HG_

#include "CGameObject.h"		// (also has string)
#include <vector>	

class IFactory		// Things that can create object see this
{
public:
	virtual ~IFactory() {};		// implement a desructor for this
	// Returns a "handle" (aka an ID) of the object (NOT a pointer, though)
	virtual unsigned int CreateObjectByType(std::string type, std::string filename ) = 0;
	virtual unsigned int CreateObjectByType(std::string type, std::string filename, CVector3f initPosition) = 0;
	virtual unsigned int CreateObjectByType(std::string type, std::string filename, CVector3f initPosition, float initScale) = 0;
	// Added
	virtual unsigned int CreateObject( CMessage theCreationParams ) = 0;
	//
	virtual bool UpdateObjectPositionByID( unsigned int ID, CVector3f newPosition ) = 0;
	virtual bool UpdateObjectScaleByID( unsigned int ID, float newScale ) = 0;
	virtual bool UpdateObjectVelocityByID( unsigned int ID, CVector3f newVelocity ) = 0;
	virtual bool UpdateObjectRotationByID( unsigned int ID, CVector3f newRotation ) = 0;
	virtual bool UpdatePlyFileByID( unsigned int ID, std::string newPlyFileName ) = 0;
	// ADDED on September 29, 2014
	virtual bool UpdateColourByID( unsigned int ID, CVector3f newColour ) = 0;

	// Called by the renderer
	virtual void getRenderedObjects(std::vector< CGameObject* > &vecObjectsToRender) = 0;
	// This is called by the physics updater
	virtual void getPhysicsObjects(std::vector< CGameObject* > &vecObjectsToUpdate ) = 0;
};

#endif
