#ifndef __ASENIGNE_LUA_TYPE_H
#define __ASENIGNE_LUA_TYPE_H

#include "Core/String/UniqueString.h"

namespace ASEngine
{
    // base cpp type
    class LuaCppType
    {
    public:
        LuaCppType(UniqueString name);
        virtual ~LuaCppType();

        // get type name
        inline UniqueString GetName() const
        {
            return m_Name;
        }
    private:
        UniqueString m_Name{};
    };
} // namespace ASEngine


#endif // __ASENIGNE_LUA_TYPE_H