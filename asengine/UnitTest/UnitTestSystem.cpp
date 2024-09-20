#include "UnitTestSystem.h"
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
        std::vector<std::string> failedTestCases = {};
        auto runTest = [&err, &failedTestCases] (std::unique_ptr<UnitTest>& test)
        {
            int errCode = test->Run();
            if (errCode)
                failedTestCases.push_back(test->GetTestSuitName());
            err |= errCode;
        };

        // get arguments
        const auto& arguments = ASEngine::GetInstance().GetArguments();

        // run specific test if arguments are set
        if (arguments.size() > 1)
        {
            for (size_t i = 1; i < arguments.size(); i++)
            {
                const auto& testCase = arguments[i];

                if (m_Tests.find(testCase) != m_Tests.end())
                    runTest(m_Tests[testCase]);
            }
        }
        // run all tests
        else
        {
            for (auto& [name, test]: m_Tests)
            {
                runTest(test);
            }
        }

        // exit with error code of all tests
        if (err)
        {
            Debug::Error("UnitTest(s) Failed:");
            for (const auto& failedTestCase: failedTestCases)
            {
                Debug::Error("   x", failedTestCase);
            }
        }
        ASEngine::GetInstance().Exit(err);
    }

    void UnitTestSystem::Terminate()
    {
        m_Tests.clear();
    }

} // namespace ASEngine
