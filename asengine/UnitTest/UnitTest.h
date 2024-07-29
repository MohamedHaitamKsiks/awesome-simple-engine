#ifndef __ASENGINE_UNIT_TEST_H
#define __ASENGINE_UNIT_TEST_H

#include "Macros/Foreach.h"
#include "Core/Error/Exception.h"
#include "Core/Debug/Debug.h"

#include<cstdlib>

#include<unordered_map>
#include<string>
#include<functional>
#include<stdexcept>
#include<chrono>



// unit test expect predicat
#define ASENGINE_EXPECT(predicat) ASEngine::UnitTest::Expect(predicat, __FILE__, __LINE__, #predicat)

namespace ASEngine
{
    // unit test container
    class  UnitTest
    {
    public:
        UnitTest() = default;
        virtual ~UnitTest() {};

        // run tests and returns 0 if it's OK
        int Run(); 

    protected:
        // describe test suit
        virtual void Describe() = 0;
        
        // add test case
        void Test(const std::string& testCaseName, const std::function<void()>& testCallback);

        // assertion
        static void Expect(bool predicat, const std::string &file, uint32_t line, const std::string &errorMessage);

        // get test suit name
        inline const std::string& GetTestSuitName() const
        {
            return m_TestSuitName;
        }

    private:
        friend class UnitTestSystem;
        // test suits
        std::unordered_map<std::string, std::function<void()>> m_TestCases{};
        std::vector<std::string> m_TestCasesName{}; // to have them run by order of insertion
        std::string m_TestSuitName = "TestSuit";
    };
} // namespace ASEngine


#endif // __ASENGINE_UNIT_TEST_H