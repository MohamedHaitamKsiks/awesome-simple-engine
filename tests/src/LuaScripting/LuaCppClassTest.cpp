#include "LuaCppClassTest.h"

namespace ASEngine
{
    class Animal
    {
    public:
        Animal(const std::string& name): m_Name(name)
        {
        }

        virtual void SayHello() const = 0;
        virtual ~Animal() {}

        int NextAge(int offset)
        {   
            m_Age += offset;
            return m_Age;
        }

        int NextAge()
        {
            return NextAge(1);
        }

        inline int GetAge() const
        {
            return m_Age;
        }

        inline const std::string& GetName() const
        {
            return m_Name;
        }

    protected:
        std::string m_Name = "";
        int m_Age = 0;
    };

    class Dog: public Animal
    {
    public:
        Dog(const std::string& name): Animal(name) {}

        ~Dog() 
        {
        }

        void SayHello() const override
        {
            Debug::Log("Ouf Ouf ", m_Name);
        }
    };

    class ZooResource: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(ZooResource);
    public:
        ~ZooResource() 
        {
        }

        void AddDog(const std::string& name)
        {
            std::unique_ptr<Animal> animal = std::make_unique<Dog>(name);
            m_Animals[name] = std::move(animal);
        }

        inline Animal& GetAnimal(const std::string& name) const
        {
            return *m_Animals.at(name);
        }

        void NextAge(int offset)
        {
            for (auto& [name, animal]: m_Animals)
            {
                animal->NextAge(offset);
            }
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<Animal>> m_Animals {};
    };
}
 
ASENGINE_SERIALIZE_RESOURCE_REF(ZooResource);


namespace ASEngine
{

    void LuaCppClassTest::Describe()
    {

        Test("It can register class", []()
        {
            // animal
            ASENGINE_LUA_CPP_CLASS_BEGIN(Animal)
            {
                ASENGINE_BIND_METHOD(SayHello);
                ASENGINE_BIND_METHOD_EXT(NextAge, int, int);
                ASENGINE_BIND_METHOD(GetAge);
                ASENGINE_BIND_METHOD(GetName);
            } ASENGINE_LUA_CPP_CLASS_END();
 
            // dog
            ASENGINE_LUA_CPP_CLASS_DERIVED_BEGIN(Dog, Animal)
            {
                ASENGINE_BIND_CONSTRUCTOR(const std::string&);
            } ASENGINE_LUA_CPP_CLASS_END();

            // run
            auto& state = LuaRuntime::GetInstance().GetState();
            state.Run(R"lua(
                function nextAges(n, dog, step)
                    for i=1,n do
                        dog:nextAge(step)
                    end
                end

                local dog = Dog.new('Ksiks')
                assert(dog:getName() == 'Ksiks')

                dog:sayHello()

                nextAges(5, dog, 2)
                assert(dog:getAge() == 5 * 2)

                dog = nil
                collectgarbage("collect") 
            )lua");
        });

        
        Test("It can register resource class", []() 
        {
            ASENGINE_REGISTER_RESOURCE_CLASS(ZooResource);
            dynamic_cast<ISystem &>(ZooResource::GetResourceClass()).Init();

            ASENGINE_LUA_CPP_CLASS_BEGIN(ZooResource)
            {
                ASENGINE_BIND_CONSTRUCTOR();
                ASENGINE_BIND_METHOD(AddDog);
                ASENGINE_BIND_METHOD(GetAnimal);
                ASENGINE_BIND_METHOD(NextAge);
            } ASENGINE_LUA_CPP_CLASS_END();
            
            auto& state = LuaRuntime::GetInstance().GetState();
            state.Run(R"lua(
                local zoo = ZooResource.new()

                zoo:addDog('Haitam')
                zoo:addDog('Mohamed')

                local haitam = zoo:getAnimal('Haitam')
                assert(haitam:getName() == 'Haitam')
                
                haitam:nextAge(2)
                assert(haitam:getAge() == 2)

                zoo:nextAge(5)
                assert(haitam:getAge() == 7)

                zoo = nil
                collectgarbage("collect") 
            )lua");

            ASENGINE_EXPECT(ZooResource::GetResourceClass().GetResourcesCount() == 0);
        });
        
    }

}
