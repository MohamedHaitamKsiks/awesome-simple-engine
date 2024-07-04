#ifndef __ASENGINE_SIGNAL_H
#define __ASENGINE_SIGNAL_H

#include <vector>
#include <functional>

#include "API/API.h"

namespace ASEngine
{
    // signal connection important to keep to disconnect when you don't need it anymore
    using SignalConnectionID = uint32_t;

    // signal class
    template <typename T, typename... types>
    class ASENGINE_API Signal
    {
    public:
        Signal() = default;
        ~Signal() = default;

        // don't allow copy / asginemnet
        Signal(const Signal&) = delete;
        Signal& operator=(const Signal&) = delete;

        // connect function to the signal with signature similar to the signal signature
        inline SignalConnectionID Connect(std::function<void(T, types...)> callback)
        {
            SignalConnectionID connectionID = static_cast<SignalConnectionID>(m_Callbacks.size());
            m_Callbacks.push_back(callback);

            return connectionID;
        }

        // disconnect
        inline void Disconnect(SignalConnectionID connection)
        {
            //m_Callbacks.Free(static_cast<ChunkID>(connection));
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
       std::vector<std::function<void(T, types...)>> m_Callbacks{};
       std::vector<SignalConnectionID> m_FreeConnectionIDs{}; 
    };

} // namespace ASEngine

#endif // __ASENGINE_SIGNAL_H