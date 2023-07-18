#ifndef ASENGINE_SYSTEM_H
#define ASENGINE_SYSTEM_H

#include <memory>
#include <functional>
#include <vector>
#include <tuple>

#include "engine/Renderer/Graphics.h"

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

        inline std::vector<std::weak_ptr<Archetype>>& GetArchetypes()
        {
            return m_Archetypes;
        };

        inline void AddArchetype(std::weak_ptr<Archetype> archetype)
        {
            m_Archetypes.push_back(archetype);
        };

        // on update
        virtual void OnUpdate(float delta) = 0;

    protected:
        // system signature with it's component requirements
        uint32_t m_Signature = 1;

        // archetypes list
        std::vector<std::weak_ptr<Archetype>> m_Archetypes = {};
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
        void ForEach(std::function<void(T*, types*...)> callback)
        {
            for (auto archetype: m_Archetypes)
            {
                ComponentCollection<T>& collection = archetype.lock()->template GetComponentCollection<T>();

                for (auto it = collection.begin(); it != collection.end(); it++)
                {   
                    ChunkID index = it.GetCurrentPosition();
                    callback(collection.Get(index), archetype.lock()->template GetComponentCollection<types>().Get(index)...);
                }
                
            }
        };

        // 
    };

} // namespace ASEngine


#endif
