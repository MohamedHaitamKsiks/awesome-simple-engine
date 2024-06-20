#ifndef __ASENGINE_SINGLETON_H
#define __ASENGINE_SINGLETON_H

#include "Core/Error/Assertion.h"
#include "Core/Debug/Debug.h"

/*
    definition for singleton template
    just to avoid rewrite alot of code that is basically the same for
    all singletons in the engine
*/

// create singleton macro
// add it in your singleton classes
#define ASENGINE_DEFINE_SINGLETON(Type) \
public: \
    \
    Type() \
    { \
        ASENGINE_ASSERT(Singleton<Type>::s_Instance == nullptr, "Singleton Already Exists!"); \
        Singleton<Type>::s_Instance = this; \
    } \
    \
    Type(const Type &) = delete; \
    Type& operator=(const Type&) = delete; \
    \
    static inline Type &GetInstance() \
    { \
        ASENGINE_ASSERT(Singleton<Type>::s_Instance, "Singleton hasn't been created yet!"); \
        return *Singleton<Type>::s_Instance; \
    } \
    static inline bool IsInstantiated() \
    { \
        return Singleton<Type>::s_Instance != nullptr; \
    } 


namespace ASEngine
{
    template <typename Type>
    class Singleton
    {
    public:
        static Type* s_Instance;
    };

    template <typename Type>
    Type *Singleton<Type>::s_Instance = nullptr;
    
} // namespace ASEngine


#endif