#include "Core/UniqueStringTest.h"
#include "Core/PoolAllocatorTest.h"
#include "Core/VectorTest.h"
#include "Object/ClassManagerTest.h"
#include "ASEngineTestSystem.h"

void ASEngineTestSystem::Registry() 
{
    //RegisterUnitTest<UniqueStringTest>("UniqueStringTest");
    //RegisterUnitTest<PoolAllocatorTest>("PoolAllocatorTest");
    //RegisterUnitTest<Vector2Test>("Vector2Test");
    //RegisterUnitTest<Vector3Test>("Vector3Test");
    RegisterUnitTest<ClassManagerTest>("ClassManagerTest");
}