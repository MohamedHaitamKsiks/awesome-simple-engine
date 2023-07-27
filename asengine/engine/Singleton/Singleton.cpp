#include "Singleton.h"

namespace ASEngine
{
    template <typename T>
    T* Singleton<T>::s_Singleton = nullptr;

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
