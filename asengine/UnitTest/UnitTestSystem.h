#ifndef __ASENGINE_UNIT_TEST_SYSTEM_H
#define __ASENGINE_UNIT_TEST_SYSTEM_H

#include <memory>
#include <string>
#include <unordered_map>
#include "UnitTest.h"
#include "ECS/System.h"
#include "Core/Singleton/Singleton.h"

#include "API/API.h"

namespace ASEngine
{
    // Inherit from to create a test application.
    // Singleton => only one test system per application.
    // Make sure to register it after all the systems you want to test.
    // Also run in headless mode.
    // The application will exit with 0 if all tests are fine.
    class ASENGINE_API UnitTestSystem : public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(UnitTestSystem);

    protected:
        ~UnitTestSystem() {};

        // register tests 
        virtual void Registry() = 0;

        // register unit test
        template<typename TestType>
        void RegisterUnitTest(const std::string& name)
        {
            std::unique_ptr<UnitTest> unitTest = std::make_unique<TestType>();
            unitTest->m_TestSuitName = name;
            m_Tests[name] = std::move(unitTest);
        }
    private:
        // all registered tests
        std::unordered_map<std::string, std::unique_ptr<UnitTest>> m_Tests{};
    
        void Init() override;
        void Terminate() override;
    };
} // namespace ASEngine


#endif // __ASENGINE_UNIT_TEST_SYSTEM_H