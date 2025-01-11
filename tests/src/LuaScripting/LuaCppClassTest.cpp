#include "LuaCppClassTest.h"

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

ASENGINE_SERIALIZE_RESOURCE_REF(ZooResource);

// singleton 
class ZooManager
{
ASENGINE_DEFINE_SINGLETON(ZooManager);
public:
    ~ZooManager() {}

    void AddZoo()
    {
        m_Zoos.push_back(ZooResource::GetResourceClass().New());
    }

    inline int GetZooCount() const
    {
        return m_Zoos.size();
    }

    ResourceRef<ZooResource> Get(int position)
    {
        return m_Zoos[position];
    }

private:
    std::vector<ResourceRef<ZooResource>> m_Zoos{};
};

void LuaCppClassTest::Describe()
{

    Test("It can register class", []()
    {
        // animal
        ASENGINE_LUA_CPP_CLASS_BEGIN(Animal)
        {
            BIND_METHOD("say_hello", SayHello);
            BIND_METHOD_EXT("next_age", NextAge, int, int);
            BIND_METHOD("get_age", GetAge);
            BIND_METHOD("get_name", GetName);
            BIND_FUNCTION("__tostring", [](Animal& animal)
            {
                return animal.GetName();
            }, false);
        } ASENGINE_LUA_CPP_CLASS_END();

        // dog
        ASENGINE_LUA_CPP_CLASS_DERIVED_BEGIN(Dog, Animal)
        {
            BIND_CONSTRUCTOR(const std::string&);
        } ASENGINE_LUA_CPP_CLASS_END();

        // run
        auto &runtime = LuaRuntime::GetInstance();
        runtime.Run(R"lua(
            function next_ages(n, dog, step)
                for i=1,n do
                    dog:next_age(step)
                end
            end

            local dog = Dog:new('Ksiks')
            assert(dog:get_name() == 'Ksiks')

            dog:say_hello()

            next_ages(5, dog, 2)
            assert(dog:get_age() == 5 * 2)

            print(dog)
        )lua");
    });

    
    Test("It can register resource class", []() 
    {
        ASENGINE_REGISTER_RESOURCE_CLASS(ZooResource);
        dynamic_cast<ISystem &>(ZooResource::GetResourceClass()).Init();

        ASENGINE_LUA_CPP_CLASS_BEGIN(ZooResource)
        {
            BIND_CONSTRUCTOR();
            BIND_METHOD("add_dog", AddDog);
            BIND_METHOD("get_animal", GetAnimal);
            BIND_METHOD("next_age", NextAge);
        } ASENGINE_LUA_CPP_CLASS_END();
        
        auto& runtime = LuaRuntime::GetInstance();
        runtime.Run(R"lua(
            local zoo = ZooResource:new()
            assert(ZooResource:get_class_name() == "ZooResource")

            zoo:add_dog('Haitam')
            zoo:add_dog('Mohamed')

            local haitam = zoo:get_animal('Haitam')
            assert(haitam:get_name() == 'Haitam')
            
            haitam:next_age(2)
            assert(haitam:get_age() == 2)

            zoo:next_age(5)
            assert(haitam:get_age() == 7)
        )lua");

        ASENGINE_EXPECT(ZooResource::GetResourceClass().GetResourcesCount() == 0);
    });


    Test("It can register singleton", []()
    {
        ZooManager manager{};

        ASENGINE_LUA_CPP_CLASS_BEGIN(ZooManager)
        {
            SET_SINGLETON();
            BIND_METHOD("add_zoo", AddZoo);
            BIND_METHOD("get_zoo_count", GetZooCount);
            BIND_METHOD("get", Get);
        }
        ASENGINE_LUA_CPP_CLASS_END();

        auto &runtime = LuaRuntime::GetInstance();
        runtime.Run(R"lua(
            ZooManager:add_zoo()
            ZooManager:add_zoo()

            assert(ZooManager:get_zoo_count() == 2)

            local zoo = ZooManager:get(0)
            zoo:add_dog('Haitam');
        )lua");
    }); 
}

