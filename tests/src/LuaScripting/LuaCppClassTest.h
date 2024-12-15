#ifndef __ASENGINE_LUA_CPP_CLASS_TEST_H
#define __ASENGINE_LUA_CPP_CLASS_TEST_H

#include "ASEngine.h"
namespace ASEngine
{
    class LuaCppClassTest: public UnitTest
    {
    public:
        ~LuaCppClassTest() {}

    private:
        void Describe() override;
    };

}

#endif // __ASENGINE_LUA_CPP_CLASS_TEST_H
