#include "ResourceTest.h"

class TestResourceType: public Resource
{
ASENGINE_DEFINE_RESOURCE(TestResourceType);
ASENGINE_SERIALIZE_RESOURCE(TestResourceType);
public:

    TestResourceType()
    {
        // Debug::Log("Hello Test Resource!");
    }

    ~TestResourceType()
    {
        // Debug::Log("Goodbye Test Resource!");
    }

    virtual int GetValue() const = 0;

private:
    friend Serializer;
    virtual void SetValue(int value) = 0;

};

ASENGINE_SERIALIZE_RESOURCE_REF(TestResourceType);

template <>
void  Serializer::Deserialize(const Json &object, TestResourceType &dest)
{
    dest.SetValue(object.at("Value").get<int>());
}

template <>
Json  Serializer::Serialize(const TestResourceType &value)
{
    Json object = Json({});
    object["Value"] = value.GetValue();
    return object;
}

ASENGINE_SERIALIZE_RESOURCE_IMP(TestResourceType);

// implementation of the resource type
// to test the possiblity of api agnostic resource
class TestResourceTypeImp: public TestResourceType
{
public:
    TestResourceTypeImp()
    {
        m_Value = 5;
    }

    int GetValue() const override
    {
        return m_Value;
    }
private:
    void SetValue(int value) override
    {
        m_Value = value;
    }

    int m_Value = 0;
};


void ResourceTest::Describe()
{
    Test("it registers resource type", []()
    {
        ASENGINE_REGISTER_ABSTRACT_RESOURCE_CLASS(TestResourceType, TestResourceTypeImp);
        dynamic_cast<ISystem&>(TestResourceType::GetResourceClass()).Init();

        ResourceRef<TestResourceType> test{};
        ASENGINE_EXPECT(test == ResourceRef<TestResourceType>::NONE());
    });

    Test("it can instanciate resource", []()
    {
        ResourceRef<TestResourceType> test = TestResourceType::GetResourceClass().New();
        ASENGINE_EXPECT(test->GetValue() == 5);
        ASENGINE_EXPECT(test != ResourceRef<TestResourceType>::NONE());
    });


    Test("it casts to parent type", []()
    {
        ResourceRef<TestResourceType> test = TestResourceType::GetResourceClass().New();
        ResourceRef<Resource> test2 = test;

        ASENGINE_EXPECT(test2->GetResourceID() == test->GetResourceID());
    });

    Test("it collects garbage", []()
    {
        std::vector<ResourceRef<TestResourceType>> tests{};
        IResourceClass& testClass = TestResourceType::GetResourceClass();

        constexpr int count = 10;

        for (int i = 0; i < count; i++)
        {

            ResourceRef<TestResourceType> test = testClass.New();
            ResourceRef<TestResourceType> test1 = test;

            // replace resource by another one
            ResourceRef<TestResourceType> test2 = testClass.New();
            test = test2;

            tests.push_back(test);

        }

        // test number of
        ASENGINE_EXPECT(testClass.GetResourcesCount() == count);

        tests.clear();
        ASENGINE_EXPECT(testClass.GetResourcesCount() == 0);
    });

    Test("it can get resource", []()
    {
        ResourceRef<TestResourceType> test = TestResourceType::GetResourceClass().Load("assets://test_resource/test.resource.json");
        test->SetPersistent(true);
    });

    Test("it is serializable", []()
    {
        Json testRefObject = Json("assets://test_resource/test.resource.json");

        ResourceRef<TestResourceType> test;
        Serializer::Deserialize(testRefObject, test);

        ASENGINE_EXPECT(test->GetValue() == 27052001);
    });

    Test("it is inline-serializable", []()
    {
        Json testRefObject = Json({});
        testRefObject["Value"] = 123;

        ResourceRef<TestResourceType> test;
        Serializer::Deserialize(testRefObject, test);

        ASENGINE_EXPECT(test->GetValue() == 123);
    });
}
