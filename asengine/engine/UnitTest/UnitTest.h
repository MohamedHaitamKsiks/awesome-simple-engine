#ifndef ASENGINE_UNIT_TEST_H
#define ASENGINE_UNIT_TEST_H

#include "Macros/Foreach.h"
#include "Core/Error/Exception.h"
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

#define EXPECT(predicat) \
    test.Expect(predicat, __FILE__, __LINE__, #predicat)

namespace ASEngine
{

    // test fail exception
    DEFINE_EXCEPTION(TestFailException, "Test Failed!");

    // unit test container
    class UnitTest
    {
    public:

        UnitTest(const std::string& testSuitName): m_TestSuitName(testSuitName) {};

        // start case
        void Test(const std::string& testCaseName, const std::function<void()>& testCallback);

        // assertion
        void Expect(bool predicat, const std::string &file, uint32_t line, const std::string &errorMessage);

        // run tests and returns if test passes are not
        bool Run(); 

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