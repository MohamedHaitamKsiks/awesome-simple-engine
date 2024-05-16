#include "ResourceTest.h"

class TestResourceType: public Resource<TestResourceType>
{
public:
    TestResourceType()
    {
        Debug::Log("Hello Test Resource!");
        m_Value = 5;
    }

    ~TestResourceType()
    {
        Debug::Log("Goodbye Test Resource!");
    }

    inline int GetValue() const
    {
        return m_Value;
    }
private:
    int m_Value = 0;
    friend class Serializer<TestResourceType>;
};

ASENGINE_SERIALIZE_RESOURCE_REF(TestResourceType);

template <>
void Serializer<TestResourceType>::Deserialize(const Json& object, TestResourceType& dest)
{
}

template <>
Json Serializer<TestResourceType>::Serialize(const TestResourceType& value)
{
    return Json({});
}


void ResourceTest::Describe()
{
    Test("it registers resource type", []()
    {
        ResourceManager::GetInstance().RegisterResourceClass<TestResourceType>(UniqueString("TestResourceType"));
    });

    Test("it can instanciate resource", []()
    {
        ResourceRef<TestResourceType> test = ResourceClass<TestResourceType>::GetInstance().New();
        ASENGINE_EXPECT(test->GetValue() == 5);
    });

    Test("it casts to parent type", []()
    {
        UniqueString referenceName("Test");

        ResourceRef<TestResourceType> test = ResourceClass<TestResourceType>::GetInstance().New(referenceName);
        ResourceRef<AbstractResource> test2 = test;
        
        ASENGINE_EXPECT(test2->GetReferenceName() == referenceName);
    });


    Test("it collect garbage ", []()
    {
        std::vector<ResourceRef<TestResourceType>> tests{};
        constexpr int count = 10;

        for (int i = 0; i < count; i++)
        {
            //Debug::Log(i);
            ResourceRef<TestResourceType> test = ResourceClass<TestResourceType>::GetInstance().New();
            ResourceRef<TestResourceType> test1 = test;
            
            // replace resource by another one
            ResourceRef<TestResourceType> test2 = ResourceClass<TestResourceType>::GetInstance().New();
            test = test2;

            tests.push_back(test);
        }

        // test number of
        ASENGINE_EXPECT(ResourceClass<TestResourceType>::GetInstance().GetResourcesCount() == count);

        tests.clear();        
        ASENGINE_EXPECT(ResourceClass<TestResourceType>::GetInstance().GetResourcesCount() == 0);
    });
}
