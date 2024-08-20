#ifndef _IMEDIATOR_H
#define _IMEDIATOR_H

#include "IPhysicsComp.h"
#include "shaderClass.h"
#include "modelData.h"
#include <vector>

class IMediator
{
public:
	virtual ~IMediator(){};
	virtual std::vector<IPhysicsComp*> fetchPhyComp() = 0;
	virtual std::vector<ModelData*> fetchModelComp() = 0;
};

#endif