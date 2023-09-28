#ifndef ASENGINE_SIGNAL_H
#define ASENGINE_SIGNAL_H

#include "Core/Memory/PoolAllocator.h"

#include <vector>
#include <functional>

namespace ASEngine
{
    // signal connection important to keep to disconnect when you don't need it anymore
    using SignalConnection = size_t;

    // signal class
    template <typename T, typename... types>
    class Signal
    {
    public:
        // connect function to the signal with signature similar to the signal signature
        SignalConnection Connect(std::function<void(T, types...)> callback);

        // disconnect
        void Disconnect(SignalConnection connection);

        // emit signal
        void Emit(T t, types... args);

    private:
        // list of functions connected to the signal
        TPoolAllocator<std::function<void(T, types...)>> m_Callbacks{2};
    };

    // include implementation template
    template <typename T, typename... types>
    SignalConnection Signal<T, types...>::Connect(std::function<void(T, types...)> callback)
    {
        return (SignalConnection)m_Callbacks.Push(callback);
    }

    template <typename T, typename... types>
    void Signal<T, types...>::Disconnect(SignalConnection connection)
    {
        m_Callbacks.Free((ChunkID)connection);
    }

    template <typename T, typename... types>
    void Signal<T, types...>::Emit(T t, types... args)
    {
        for (ChunkID id = 0; id < m_Callbacks.GetCapacity(); id++)
        {
            if (m_Callbacks.IsFree(id))
                continue;

            auto &callback = m_Callbacks.Get(id);
            callback(t, args...);
        }
    }
} // namespace ASEngine

#endif // ASENGINE_SIGNAL_H