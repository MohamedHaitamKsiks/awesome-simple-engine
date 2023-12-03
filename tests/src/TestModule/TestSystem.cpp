#include "TestSystem.h"
#include "Core/CoreTest.h"


void TestSystem::OnCreate()
{
    RUN_TESTS(
        CoreTest
    );
}