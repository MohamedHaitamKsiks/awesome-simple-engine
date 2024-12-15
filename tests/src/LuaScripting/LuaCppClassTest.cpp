#include "LuaCppClassTest.h"

namespace ASEngine
{
    class Animal
    {
    public:
        Animal(const std::string& name): m_Name(name)
        {
            Debug::Log("Constructing ", name);
        }

        virtual void SayHello() = 0;
        virtual ~Animal() {}

        int NextAge()
        {
            return ++m_Age;
        }

    protected:
        std::string m_Name = "";
        int m_Age = 0;
    };

    class Dog: public Animal
    {
    public:
        Dog(const std::string& name): Animal(name) {}

        ~Dog() {}

        void SayHello() override
        {
            Debug::Log("Ouf Ouf ", m_Name);
        }
    };


    void LuaCppClassTest::Describe()
    {
        Test("It can register class", []()
        {
            // animal
            ASENGINE_LUA_CPP_CLASS_BEGIN(Animal)
            {
                ASENGINE_BIND_METHOD(SayHello);
                ASENGINE_BIND_METHOD(NextAge);
            } ASENGINE_LUA_CPP_CLASS_END();

            // dog
            ASENGINE_LUA_CPP_CLASS_DERIVED_BEGIN(Dog, Animal)
            {
                ASENGINE_BIND_CONSTRUCTOR(std::string);
            } ASENGINE_LUA_CPP_CLASS_END();

            // run
            auto& state = LuaScriptManager::GetInstance().GetState();
            state.Run(R"lua(
                local dog = Dog.new('Ksiks')
                dog:sayHello()
                for i=1,10000 do
                    print(dog:nextAge())
                end
            )lua");
        });
    }

}
