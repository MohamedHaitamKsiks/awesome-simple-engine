#include "LuaCppClassTest.h"

namespace ASEngine
{
    class Animal
    {
    public:
        Animal(const std::string& name): m_Name(name)
        {
        }

        virtual void SayHello() = 0;
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

        int GetAge()
        {
            return m_Age;
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
                ASENGINE_BIND_METHOD_EXT(NextAge, int, int);
                ASENGINE_BIND_METHOD(GetAge);
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
                dog:sayHello()

                -- nextAges(5, dog, 2)
                -- assert(dog:getAge() == 5 * 2)
            )lua");
        });

        /*Test("It can register resource class", []() 
        {
            auto& state = LuaRuntime::GetInstance().GetState();
            state.Run(R"lua(
            
            )lua");
        });*/
    }

}
