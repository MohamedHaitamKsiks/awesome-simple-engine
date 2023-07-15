#include "Singleton.h"

namespace ASEngine
{
    template <typename T>
    T* Singleton<T>::singleton = nullptr;

    template <typename T>
    void Singleton<T>::init()
    {
        if (!singleton)
            singleton = new T();
    }

    template <typename T>
    T* Singleton<T>::getSingleton()
    {
        return singleton;
    }

    template <typename T>
    void Singleton<T>::terminate()
    {
        if (singleton)
            delete singleton;
    }


} // namespace ASEngine
