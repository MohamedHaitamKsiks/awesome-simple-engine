#ifndef ASENGINE_UNIT_TEST_H
#define ASENGINE_UNIT_TEST_H

#include "Macros/Foreach.h"
#include "Core/Error/Exception.h"
#include "Core/Debug/Debug.h"

#include<cstdlib>

#include<unordered_map>
#include<string>
#include<functional>
#include<stdexcept>
#include<chrono>

#define ASENGINE_RUN_TESTS(...) exit(FOREACH(ASENGINE_RUN_TEST, __VA_ARGS__) 0)

#define ASENGINE_RUN_TEST(test) test() |

/*
    ASENGINE_UNIT_TEST(test name, test body)
    create unit test in on cpp file
    this is the main entry to the test
*/ 
#define ASENGINE_UNIT_TEST(testName, body) \
    int testName() \
    { \
        ASEngine::UnitTest test(#testName); \
        body \
        return test.Run(); \
    } 

#define ASENGINE_UNIT_TEST_CASE(testCase, body) test.Test(testCase, [&] () { body })

#define ASENGINE_UNIT_TEST_EXPECT(predicat) test.Expect(predicat, __FILE__, __LINE__, #predicat)

namespace ASEngine
{
    // unit test container
    class UnitTest
    {
    public:

        UnitTest(const std::string& testSuitName);

        // start case
        void Test(const std::string& testCaseName, const std::function<void()>& testCallback);

        // assertion
        void Expect(bool predicat, const std::string &file, uint32_t line, const std::string &errorMessage);

        // run tests and returns 0 if it's OK
        int Run(); 

        // get test suit name
        inline const std::string& GetTestSuitName() const
        {
            return m_TestSuitName;
        }

    private:
        // test suits
        std::unordered_map<std::string, std::function<void()>> m_TestCases{};
        std::string m_TestSuitName = "TestSuit";
    };
} // namespace ASEngine


#endif // ASENGINE_UNIT_TEST_H