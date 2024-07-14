#include "UnitTest.h"
#define SEC_TO_MILL 1000.0f
#define DEBUG_PRINT_LINE() Debug::Log("_______________________________________________________________\n")


namespace ASEngine
{
    // test fail exception
    ASENGINE_DEFINE_EXCEPTION(TestFailException, "Test Failed!");

    void UnitTest::Test(const std::string &testCaseName, const std::function<void()> &testCallback)
    {
        m_TestCases[testCaseName] = testCallback;
        m_TestCasesName.push_back(testCaseName);
    }

    void UnitTest::Expect(bool predicat, const std::string& file, uint32_t line, const std::string& errorMessage )
    {
        if (!predicat)
        {
            std::stringstream errorSS;
            errorSS << file << ":" << line << ": Wrong predicat: " << errorMessage;
            throw TestFailException(errorSS.str().c_str());
        }
    }

    int UnitTest::Run()
    {
        // run describe
        Describe();

        int error = 0;

        int successCount = 0;
        float totalTime = 0.0f;

        // run print header
        Debug::Log("");
        DEBUG_PRINT_LINE();
        Debug::Log(m_TestSuitName, ":");
        Debug::Log("");

        for (const auto& testName : m_TestCasesName)
        {
            const auto& testCallback = m_TestCases[testName];

            try
            {
                // get time now
                const auto pastTime = std::chrono::high_resolution_clock::now();

                // run tests
                testCallback();

                // get test duraction
                // compute delta
                const auto currentTime = std::chrono::high_resolution_clock::now();
                float delta = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count() / SEC_TO_MILL;
                totalTime += delta;

                successCount++;
                Debug::Log(Debug::Colorized(Debug::GREEN_FG,"  ✓", testName, "(", delta, "ms )"));
            }
            catch (TestFailException& failException)
            {
                error = 1;
                Debug::Error("  x", testName);
                Debug::Error("\t", failException.what());
            }

        }

        // print result
        Debug::Log("");
        Debug::Log("Tests:", Debug::Colorized(Debug::GREEN_FG, successCount, "Passed,"), m_TestCases.size(), "Total");
        Debug::Log("Time: ", totalTime, "ms");
        DEBUG_PRINT_LINE();
        Debug::Log("");

        return error;
    }


} // namespace ASEngine