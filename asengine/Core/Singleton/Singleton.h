#ifndef ASENGINE_SINGLETON_H
#define ASENGINE_SINGLETON_H

#include "Core/Error/Assertion.h"
#include "Core/Debug/Debug.h"

namespace ASEngine
{

    /*
        definition for singleton template
        just to avoid rewrite alot of code that is basically the same for
        all singletons in the engine
    */
    template<typename T>
    class Singleton
    {
        public:
            // default constructor is by default initializing singleton
            Singleton()
            {
                InitSingleton();
            };

            // make it polymorphic
            virtual ~Singleton() = default;

            // don't allow copy
            Singleton(const Singleton<T> &) = delete;
            Singleton(const T&) = delete;
            
            // get singleton instance
            static inline T& GetInstance() 
            {
                ASENGINE_ASSERT(s_Instance, std::string(typeid(T).name()) + "Singleton hasn't been created yet!");
                return *s_Instance; 
            };
            
        protected:
            static T* s_Instance;

            // call init singelton if not done by default constructor
            void InitSingleton()
            {
                ASENGINE_ASSERT(s_Instance == nullptr, "Singleton Already Exists!");
                s_Instance = (T *)(this);
            }
    };

    template <typename T>
    T* Singleton<T>::s_Instance = nullptr;

} // namespace ASEngine

#endif