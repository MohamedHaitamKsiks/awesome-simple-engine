#ifndef ASENGINE_SYSTEM_H
#define ASENGINE_SYSTEM_H

#include <memory>
#include <functional>
#include <vector>
#include <tuple>

#include "Core/InputSystem/InputEvent.h"
#include "Core/Memory/DynamicArray.h"

#include "Archetype.h"
#include "Component.h"
#include "ComponentManager.h"

namespace ASEngine
{
    // base system class
    class BaseSystem
    {
    public:

        // get priority
        inline int GetPriority() const
        {
            return m_Priority;
        };

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

        // on create
        virtual void OnCreate() {};

        // on update
        virtual void OnUpdate(float delta) {};

        // on render
        virtual void OnRender2D() {};

        // on input event
        virtual void OnInputEvent(const InputEvent& event) {};

    protected:
        // system signature with it's component requirements
        uint32_t m_Signature = 1;

        // system priority
        int m_Priority = 0;

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
                std::tuple<ComponentCollection<types> &...> collections(archetype.lock()->template GetComponentCollection<types>()...);

                for (ComponentIndex i = 0; i < collection.GetSize(); i++)
                {   
                    std::apply([callback, &collection, &i] (ComponentCollection<types> &... collections)
                    {
                        callback(collection[i], collections[i]...);
                    }, collections);

                }
            }
        };

    };

} // namespace ASEngine


#endif
