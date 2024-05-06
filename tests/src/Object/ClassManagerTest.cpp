#include "ClassManagerTest.h"

class TestClass: public TObject<TestClass>
{
public:
    TestClass() = default;

    void SayHello()
    {
        Debug::Log("Hello");
    }

private:

};

void ClassManagerTest::Describe()
{
    Test("It can be registered", []()
    {
        ClassManager::GetInstance().RegisterClass<TestClass>(UniqueString("TestClass"));
    });

    Test("It can be instanciated", []()
    {
        Object* instance = TestClass::GetClass().New();
        ASENGINE_EXPECT(instance->GetClassName() == UniqueString("TestClass"));
    
        TestClass* testInstance = dynamic_cast<TestClass*>(instance);
        ASENGINE_EXPECT(testInstance);

        TestClass::GetClass().Destroy(instance);
    });
}