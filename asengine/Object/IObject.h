#ifndef ASENGINE_IOBJECT_H
#define ASENGINE_IOBJECT_H

#include "Core/String/UniqueString.h"

namespace ASEngine
{
    // template of generic object 
    class IObject
    {
    public:
        virtual UniqueString GetClassName() const = 0;
    };
} // namespace ASEngine


#endif // ASENGINE_IOBJECT_H