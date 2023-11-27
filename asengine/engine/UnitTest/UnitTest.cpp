#include "UnitTest.h"

void ASEngine::UnitTest::Test(const std::string &testCaseName, const std::function<void()> &testCallback)
{
    m_TestCases[testCaseName] = testCallback;
}

void ASEngine::UnitTest::Expect(bool predicat)
{
    if (!predicat)
        throw TestFailException();

}

bool ASEngine::UnitTest::Run()
{
    bool testResult = true;

    for (auto const &[testName, testCallback] : m_TestCases)
    {
        try
        {
            testCallback();
            Debug::Log(testName, " PASS");
        }
        catch (TestFailException failException)
        {
            testResult = false;
            Debug::Log(testName, " FAILED");
        }
    }

    return testResult;
}