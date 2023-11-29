#ifndef ASENGINE_UNIT_TEST_H
#define ASENGINE_UNIT_TEST_H

#include "Core/Log/Log.h"

#include<cstdlib>

#include<unordered_map>
#include<string>
#include<functional>
#include<stdexcept>

#define RUN_TESTS(test) exit(1 - static_cast<int>(test.Run()))

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
        char* exceptionMessage = (char*) "Test Fail Exception";
    };


    // unit test container
    class UnitTest
    {
    public:
        // start case
        void Test(const std::string& testCaseName, const std::function<void()>& testCallback);

        // assertion
        void Expect(bool predicat);

        // run tests and returns if test passes are not
        bool Run(); 

    private:
        // test suits
        std::unordered_map<std::string, std::function<void()>> m_TestCases{};

    };
} // namespace ASEngine


#endif // ASENGINE_UNIT_TEST_H