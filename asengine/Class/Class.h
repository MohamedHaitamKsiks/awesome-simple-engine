#ifndef ASENGINE_CLASS_H
#define ASENGINE_CLASS_H

#include "Core/String/UniqueString.h"

// add inside class we want to register with a name
#define ASENGINE_DEFINE_CLASS(Type) \
public: \
    static inline UniqueString GetName() \
    { \
        return Class<Type>::GetName(); \
    } \
    UniqueString GetClassName() const override \
    { \
        return GetName(); \
    }

namespace ASEngine
{

    // implementation of generic object
    template<typename T>
    class Class
    {
    public:
        // get class name 
        static inline UniqueString GetName()
        {
            return s_ClassName;
        }

    private:
        friend class ClassManager;
        static UniqueString s_ClassName;
    };

    template <typename T>
    UniqueString Class<T>::s_ClassName;

} // namespace ASEngine


#endif // ASENGINE_CLASS_H