#ifndef ASENGINE_SIGNAL_H
#define ASENGINE_SIGNAL_H

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
        std::vector<std::function<void(T, types...)>> m_Callbacks = {};
    };
} // namespace ASEngine

// include implementation template
#include "Signal.cpp"

#endif // ASENGINE_SIGNAL_H