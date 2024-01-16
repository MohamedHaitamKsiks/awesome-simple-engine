#include "UnitTest.h"
#define SEC_TO_MILL 1000.0f

#define PRINT_LINE Debug::Log("_______________________________________________________________\n")

void ASEngine::UnitTest::Test(const std::string &testCaseName, const std::function<void()> &testCallback)
{
    m_TestCases[testCaseName] = testCallback;
}

void ASEngine::UnitTest::Expect(bool predicat, const std::string& file, uint32_t line, const std::string& errorMessage )
{
    if (!predicat)
    {
        std::stringstream errorSS;
        errorSS << file << ":" << line << ": Wrong predicat: " << errorMessage;
        throw TestFailException(errorSS.str());
    }
}

bool ASEngine::UnitTest::Run()
{
    bool testResult = true;

    int successCount = 0;
    float totalTime = 0.0f;

    // run print header
    Debug::Log("");
    PRINT_LINE;
    Debug::Log(m_TestSuitName, ":");
    Debug::Log("");

    for (auto const &[testName, testCallback] : m_TestCases)
    {
        try
        {
            // get time now
            auto pastTime = std::chrono::high_resolution_clock::now();

            // run tests
            testCallback();

            // get test duraction
            // compute delta
            auto currentTime = std::chrono::high_resolution_clock::now();
            float delta = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count() / SEC_TO_MILL;
            totalTime += delta;

            successCount++;
            Debug::Log(Debug::Colorized(Debug::GREEN_FG,"  ✓", testName, "(", delta, "ms )"));
        }
        catch (TestFailException failException)
        {
            testResult = false;
            Debug::Error("  x", testName);
            Debug::Error("\t", failException.what());
        }

    }

    // print result
    Debug::Log("");
    Debug::Log("Tests:", Debug::Colorized(Debug::GREEN_FG, successCount, "Passed,"), m_TestCases.size(), "Total");
    Debug::Log("Time: ", totalTime, "ms");
    PRINT_LINE;
    Debug::Log("");

    return testResult;
}