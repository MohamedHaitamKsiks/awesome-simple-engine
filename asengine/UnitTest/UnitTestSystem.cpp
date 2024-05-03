#include "UnitTestSystem.h"
#include <cstdlib>
#include "Core/Debug/Debug.h"

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
        exit(err);
    }

} // namespace ASEngine
