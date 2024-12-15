#ifndef __ASENGINE_OBJECT_H
#define __ASENGINE_OBJECT_H

#include "Core/String/UniqueString.h"


namespace ASEngine
{
    // base class of asengine objects (Resources and Components)
    class  Object
    {
    public:
        virtual ~Object() {}
        virtual UniqueString GetClassName() const = 0;
    };
} // namespace ASEngine


#endif // __ASENGINE_OBJECT_H
