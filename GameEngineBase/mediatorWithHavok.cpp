#include "mediatorWithHavok.h"
// Keycode
#include <Common/Base/keycode.cxx>
#include <Common/Base/Config/hkProductFeatures.cxx>



#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>


#include <sstream>


HavokMediator::HavokMediator()
{

		hkMemoryAllocator* baseMalloc = hkMallocAllocator::m_defaultMallocAllocator;
}

void HavokMediator::havokInit()
{
		hkMemoryAllocator* baseMalloc = hkMallocAllocator::m_defaultMallocAllocator;
}
HavokMediator::~HavokMediator()
{

}