#ifndef __ASENGINE_SIGNAL_H
#define __ASENGINE_SIGNAL_H

#include <vector>
#include <functional>
#include <cstdint>



namespace ASEngine
{
    // signal connection important to keep to disconnect when you don't need it anymore
    using SignalConnectionID = uint32_t;

    // signal class
    template <typename T, typename... types>
    class  Signal
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
            SignalConnectionID connectionID;
            if (m_FreeConnectionIDs.size() > 0)
            {
                connectionID = m_FreeConnectionIDs.back();
                m_FreeConnectionIDs.pop_back();
            }
            else
            {
                connectionID = m_MaxSignalID;
                m_MaxSignalID++;
            }

            m_Callbacks[connectionID] = callback;

            return connectionID;
        }

        // disconnect
        inline void Disconnect(SignalConnectionID connectionID)
        {
            m_FreeConnectionIDs.push_back(connectionID);
            m_Callbacks.erase(connectionID);
        }

        // emit signal
        void Emit(T t, types... args)
        {
            for (auto& [connectionID, callback]: m_Callbacks)
            {
                callback(t, args...);
            }
        }

    private:
        // list of functions connected to the signal
       std::unordered_map<SignalConnectionID, std::function<void(T, types...)>> m_Callbacks{};
       std::vector<SignalConnectionID> m_FreeConnectionIDs{};
       SignalConnectionID m_MaxSignalID = 0;
    };

} // namespace ASEngine

#endif // __ASENGINE_SIGNAL_H
