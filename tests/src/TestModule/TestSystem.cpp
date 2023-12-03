#include "TestSystem.h"
#include "Core/UniqueStringTest.h"

void TestSystem::OnCreate()
{
    RUN_TESTS(
        UniqueStringTest);
}