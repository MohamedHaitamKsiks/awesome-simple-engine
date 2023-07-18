#ifndef ASENGINE_ARCHETYPE_MANAGER_H
#define ASENGINE_ARCHETYPE_MANAGER_H

#include <unordered_map>
#include <memory>

#include "engine/Singleton/Singleton.h"
#include "Archetype.h"

#include "System.h"
#include "SystemManager.h"

namespace ASEngine
{
    class ArchetypeManager:public Singleton<ArchetypeManager>
    {
    public:
        // get archetype internal
        template <typename T, typename... types>
        static inline std::shared_ptr<Archetype> GetArchetype() { return GetSingleton()->IGetArchetype<T, types...>(); }

    private:
        // get archetype internal
        template <typename T, typename... types>
        std::shared_ptr<Archetype> IGetArchetype();

        // create archetype
        template <typename T, typename... types>
        void CreateArchetype();

        // create archetype
        bool HasArchetype(uint32_t signature) const;

        // map signature to corresponding archetype
        std::unordered_map<uint32_t, std::shared_ptr<Archetype>> m_Archetypes = {};
    };

    // implemetations
    // get archetype implementation
    template <typename T, typename... types>
    std::shared_ptr<Archetype> ArchetypeManager::IGetArchetype()
    {
        uint32_t signature = ComponentManager::GetSignature<T, types...>();
        // is archetype doesn't exist create it
        if (!HasArchetype(signature))
        {
            CreateArchetype<T, types...>();
        }

        return m_Archetypes[signature];
    }

    // create archetype implementation
    template <typename T, typename... types>
    void ArchetypeManager::CreateArchetype()
    {
        uint32_t signature = ComponentManager::GetSignature<T, types...>();
        std::shared_ptr<Archetype> archetype = std::make_shared<Archetype>();

        archetype->AddComponents<T, types...>();
        m_Archetypes[signature] = archetype;
        
        SystemManager::RegisterArchetype(archetype);

    }

} // namespace ASEngine


#endif