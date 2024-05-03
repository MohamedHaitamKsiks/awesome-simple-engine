#include "Core/UniqueStringTest.h"
#include "Core/PoolAllocatorTest.h"
#include "ASEngineTestSystem.h"

void ASEngineTestSystem::Registry() 
{
    RegisterUnitTest<UniqueStringTest>("UniqueStringTest");
    RegisterUnitTest<PoolAllocatorTest>("PoolAllocatorTest");
}