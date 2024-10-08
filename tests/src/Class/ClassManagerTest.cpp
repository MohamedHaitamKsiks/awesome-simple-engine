#include "ClassManagerTest.h"

class TestClass: public Object
{
ASENGINE_DEFINE_CLASS(TestClass);
public:
    TestClass() = default;
};

void ClassManagerTest::Describe()
{
    Test("It can be registered", []()
    {
        ClassManager::GetInstance().RegisterClass<TestClass>(UniqueString("TestClass"));
    });

    Test("It has a name", []()
    {
        TestClass t{};
        ASENGINE_EXPECT(t.GetClassName() == UniqueString("TestClass"));
    });
}