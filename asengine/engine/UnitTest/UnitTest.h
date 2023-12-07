#ifndef ASENGINE_UNIT_TEST_H
#define ASENGINE_UNIT_TEST_H

#include "Macros/Foreach.h"
#include "Core/Log/Log.h"

#include<cstdlib>

#include<unordered_map>
#include<string>
#include<functional>
#include<stdexcept>
#include<chrono>

#define RUN_TESTS(...) exit(FOREACH(RUN_TEST, __VA_ARGS__) 0)

#define RUN_TEST(test) test() + 

#define UNIT_TEST(testName, body)   \
    int testName() {                \
        ASEngine::UnitTest test(#testName);  \
        body                        \
        return 1 - static_cast<int>(test.Run()); \
    } 

#define UNIT_TEST_CASE(testCase, body) ( test.Test(testCase, [&] () { body }) )

#define EXPECT(predicat) test.Expect(predicat)

namespace ASEngine
{

    // test fail exception
    class TestFailException: public std::exception
    {
    public:
        char *what()
        {
            return exceptionMessage;
        }
    private:
        char* exceptionMessage = const_cast<char*>("Test Fail Exception");
    };


    // unit test container
    class UnitTest
    {
    public:

        UnitTest(const std::string& testSuitName): m_TestSuitName(testSuitName) {};

        // start case
        void Test(const std::string& testCaseName, const std::function<void()>& testCallback);

        // assertion
        void Expect(bool predicat);

        // run tests and returns if test passes are not
        bool Run(); 

    private:
        // test suits
        std::unordered_map<std::string, std::function<void()>> m_TestCases{};
        std::string m_TestSuitName = "TestSuit";

    };
} // namespace ASEngine


#endif // ASENGINE_UNIT_TEST_H