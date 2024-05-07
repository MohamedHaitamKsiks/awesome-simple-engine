#ifndef ASENGINE_OBJECT_IMP_H
#define ASENGINE_OBJECT_IMP_H

#include "IObject.h"
#include "Core/String/UniqueString.h"

namespace ASEngine
{

    // implementation of generic object
    template<typename T>
    class Object: public IObject
    {
    public:
        UniqueString GetClassName() const override
        {
            return GetName();
        }

        // get class name 
        static UniqueString GetName()
        {
            return s_ClassName;
        }

    private:
        friend class ClassManager;
        static UniqueString s_ClassName;
    };

    template <typename T>
    UniqueString Object<T>::s_ClassName;

} // namespace ASEngine


#endif // ASENGINE_OBJECT_IMP_H