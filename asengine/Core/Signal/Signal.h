#ifndef ASENGINE_SIGNAL_H
#define ASENGINE_SIGNAL_H

#include "Core/Memory/PoolAllocator.h"

#include <vector>
#include <functional>

namespace ASEngine
{
    // signal connection important to keep to disconnect when you don't need it anymore
    using SignalConnectionID = ChunkID;

    // signal class
    template <typename T, typename... types>
    class Signal
    {
    public:
        // connect function to the signal with signature similar to the signal signature
        inline SignalConnectionID Connect(std::function<void(T, types...)> callback)
        {
            return static_cast<SignalConnectionID>(m_Callbacks.Push(callback));
        }

        // disconnect
        inline void Disconnect(SignalConnectionID connection)
        {
            m_Callbacks.Free(static_cast<ChunkID>(connection));
        }

        // emit signal
        void Emit(T t, types... args)
        {
            for (auto& callback: m_Callbacks)
            {
                callback(t, args...);
            }
        }

    private:
        // list of functions connected to the signal
        PoolAllocator<std::function<void(T, types...)>> m_Callbacks{2};
    };

} // namespace ASEngine

#endif // ASENGINE_SIGNAL_H