


#include <Common/Base/hkBase.h>

#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>

// Visual Debugger includes
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>

class HavokMediator
{
public :
	HavokMediator();
	virtual ~HavokMediator();
	void havokInit();
};