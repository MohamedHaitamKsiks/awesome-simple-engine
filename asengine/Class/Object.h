#ifndef __ASENGINE_OBJECT_H
#define __ASENGINE_OBJECT_H

#include "Core/String/UniqueString.h"
#include "API/API.h"

namespace ASEngine
{
    // base class of asengine objects (Resources and Components)
    class ASENGINE_API Object
    {
    public:
        virtual UniqueString GetClassName() const = 0;
    };
} // namespace ASEngine


#endif // __ASENGINE_OBJECT_H