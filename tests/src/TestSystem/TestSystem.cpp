#include "TestSystem.h"
#include "Core/UniqueStringTest.h"

void TestSystem::Init()
{
    ASENGINE_RUN_TESTS(UniqueStringTest);
}