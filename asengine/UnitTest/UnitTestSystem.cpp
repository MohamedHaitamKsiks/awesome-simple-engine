#include "UnitTestSystem.h"
#include "Core/Debug/Debug.h"
#include "Core/ASEngine/ASEngine.h"

#include <cstdlib>

namespace ASEngine
{

    void UnitTestSystem::Init()
    {
        // register unit tests
        Registry();

        // run
        int err = 0;

        for (auto& [name, test]: m_Tests)
        {
            err |= test->Run();
        }

        // exit with error code of all tests
        ASEngine::GetInstance().Exit(err);
    }

    void UnitTestSystem::Terminate()
    {
        m_Tests.clear();
    }

} // namespace ASEngine
