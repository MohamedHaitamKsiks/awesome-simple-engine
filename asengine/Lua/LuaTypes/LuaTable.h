#ifndef __ASENGINE_LUA_TABLE_H
#define __ASENIGNE_LUA_TABLE_H

#include <string>

namespace ASEngine
{
    class LuaTable
    {
    public:
        ~LuaTable();

        template <typename K, typename V>
        void Set(const K& key, V value)
        {

        }

        template <typename K, typename V>
        V Get(const K& key)
        {
            return V{};
        }

    private:
        // put value from the stack into the tabe with a key
        void SetFromStack(int keyPosition, int valuePostion);

        // get value and put it on top of the stack
        void GetToStack(int keyPostion);

        int m_StackIndex = 0;
    };
} // namespace ASEngine


#endif // __ASENIGNE_LUA_TABLE_H