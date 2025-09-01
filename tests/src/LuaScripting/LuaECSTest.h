#ifndef __ASENGINE_LUA_ECS_TEST_H
#define __ASENGINE_LUA_ECS_TEST_H

namespace ASEngine
{
    class LuaECSTest : public UnitTest
    {
    public:
        ~LuaECSTest() {}

    private:
        void Describe() override;
    };
} // namespace ASEngine


#endif // __ASENGINE_LUA_ECS_TEST_H