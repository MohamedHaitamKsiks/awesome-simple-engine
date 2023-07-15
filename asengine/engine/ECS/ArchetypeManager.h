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
        std::shared_ptr<Archetype> getArchetype();

    private:
        // create archetype
        template <typename T, typename... types>
        void createArchetype();

        // create archetype
        bool hasArchetype(uint32_t signature) const;

        // map signature to corresponding archetype
        std::unordered_map<uint32_t, std::shared_ptr<Archetype>> archetypes = {};
    };

    // implemetations
    // get archetype implementation
    template <typename T, typename... types>
    std::shared_ptr<Archetype> ArchetypeManager::getArchetype()
    {
        uint32_t signature = ComponentManager::getSingleton()->getSignature<T, types...>();
        // is archetype doesn't exist create it
        if (!hasArchetype(signature))
        {
            createArchetype<T, types...>();
        }

        return archetypes[signature];
    }

    // create archetype implementation
    template <typename T, typename... types>
    void ArchetypeManager::createArchetype()
    {
        uint32_t signature = ComponentManager::getSingleton()->getSignature<T, types...>();
        std::shared_ptr<Archetype> archetype = std::make_shared<Archetype>();

        archetype->addComponents<T, types...>();
        archetypes[signature] = archetype;
        
        SystemManager::getSingleton()->registerArchetype(archetype);

    }

} // namespace ASEngine


#endif