#ifndef ASENGINE_SINGLETON_H
#define ASENGINE_SINGLETON_H

#include "Core/Log/Log.h"

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
            // init singleton
            static void Init();
            // get singleton
            static inline T *GetSingleton() { return s_Singleton; };
            // terminate singleton
            static void Terminate(); 

        protected:
            static T* s_Singleton;
    };

    template <typename T>
    T *Singleton<T>::s_Singleton = nullptr;

    template <typename T>
    void Singleton<T>::Init()
    {
            if (!s_Singleton)
                s_Singleton = new T();
    }

    template <typename T>
    void Singleton<T>::Terminate()
    {
            if (s_Singleton)
                delete s_Singleton;
    }

} // namespace ASEngine

#endif