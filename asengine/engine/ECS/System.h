#ifndef ASENGINE_SYSTEM_H
#define ASENGINE_SYSTEM_H

#include <memory>
#include <functional>
#include <vector>
#include <tuple>

#include "engine/Memory/DynamicArray.h"

#include "Archetype.h"
#include "Component.h"
#include "ComponentManager.h"

namespace ASEngine
{
    // base system class
    class BaseSystem
    {
    public:

        // get signature
        inline uint32_t GetSignature() const
        {
            return m_Signature;
        };

        inline TDynamicArray<std::weak_ptr<Archetype>>& GetArchetypes()
        {
            return m_Archetypes;
        };

        inline void AddArchetype(std::weak_ptr<Archetype> archetype)
        {
            m_Archetypes.Push(archetype);
        };

        // on update
        virtual void OnUpdate(float delta) = 0;

    protected:
        // system signature with it's component requirements
        uint32_t m_Signature = 1;

        // archetypes list
        TDynamicArray<std::weak_ptr<Archetype>> m_Archetypes{};
    };


    // system interaface
    template <typename T, typename... types>
    class System: public BaseSystem
    {
    public:
        // constructor
        System() 
        {
            m_Signature = ComponentManager::GetSignature<T, types...>();
        };

        // foreach entiy with signature of system
        void ForEach(std::function<void(T&, types&...)> callback)
        {
            for (auto archetype: m_Archetypes)
            {
                ComponentCollection<T>& collection = archetype.lock()->template GetComponentCollection<T>();

                for (ComponentIndex i = 0; i < collection.GetSize(); i++)
                {   
                    callback(collection[i], archetype.lock()->template GetComponentCollection<types>()[i]...);
                }
                
            }
        };

        // 
    };

} // namespace ASEngine


#endif
