#ifndef ASENGINE_OBJECT_IMP_H
#define ASENGINE_OBJECT_IMP_H

#include "Object.h"
#include "Class.h"
#include "ClassManager.h"

#include "Core/String/UniqueString.h"

namespace ASEngine
{

    // implementation of generic object
    template<typename T>
    class TObject: public Object
    {
    public:
        UniqueString GetClassName() const
        {
            return GetName();
        }

        // get class name 
        static UniqueString GetName()
        {
            return TClass<T>::GetInstance().GetName();
        }

        // get class
        static Class& GetClass()
        {
            return ClassManager::GetInstance().GetClass(GetName());
        }
    };
} // namespace ASEngine


#endif // ASENGINE_OBJECT_IMP_H