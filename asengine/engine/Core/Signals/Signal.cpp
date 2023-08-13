#include "Signal.h"

namespace ASEngine
{
    template <typename T, typename... types>
    SignalConnection Signal<T, types...>::Connect(std::function<void(T, types...)> callback)
    {
        m_Callbacks.push_back(callback);
        return m_Callbacks.size() - 1;
    }

    template <typename T, typename... types>
    void Signal<T, types...>::Disconnect(SignalConnection connection)
    {
        m_Callbacks.erase(m_Callbacks.begin() + connection);
    }

    template <typename T, typename... types>
    void Signal<T, types...>::Emit(T t, types... args)
    {
        for (auto callback: m_Callbacks)
        {
            callback(t, args...);
        }
    }
} // namespace ASEngine
