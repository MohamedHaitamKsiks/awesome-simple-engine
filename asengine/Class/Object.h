#ifndef ASENGINE_OBJECT_H
#define ASENGINE_OBJECT_H

#include "Core/String/UniqueString.h"

namespace ASEngine
{
    // base class of asengine objects (Resources and Components)
    class Object
    {
    public:
        virtual UniqueString GetClassName() const = 0;
    };
} // namespace ASEngine


#endif // ASENGINE_OBJECT_H