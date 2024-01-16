#include "TestSystem.h"
#include "Core/UniqueStringTest.h"
#include "Renderer/ShaderManagerTest.h"

void TestSystem::OnCreate()
{
    RUN_TESTS(
        UniqueStringTest,
        ShaderManagerTest);
}