#ifndef ASENGINE_ARCHETYPE_MANAGER_H
#define ASENGINE_ARCHETYPE_MANAGER_H

#include <unordered_map>
#include <memory>
#include <set>

#include "Core/Memory/DynamicArray.h"
#include "Core/Singleton/Singleton.h"

#include "Archetype.h"
#include "Signature.h"

#include "System.h"
#include "SystemManager.h"

namespace ASEngine
{
    class ArchetypeManager:public Singleton<ArchetypeManager>
    {
    public:
        // get archetype 
        template <typename T, typename... types>
        static inline std::shared_ptr<Archetype> GetArchetype() { return GetSingleton()->IGetArchetype<T, types...>(); }

        // get archetype by list of component names
        static inline std::shared_ptr<Archetype> GetArchetype(const Signature& signature) { return GetSingleton()->IGetArchetype(signature); }
        

    private:
        // get archetype internal
        template <typename T, typename... types>
        std::shared_ptr<Archetype> IGetArchetype();

        // get archetype by list of component names internal
        std::shared_ptr<Archetype> IGetArchetype(const Signature& signature);

        // create archetype
        template <typename T, typename... types>
        void CreateArchetype();

        // create archetype based on list of component names
        void CreateArchetype(const Signature& signature);

        // has signature
        bool HasArchetype(const Signature& signature) const;

        // map signature to corresponding archetype
        std::unordered_map<Signature, std::shared_ptr<Archetype>> m_Archetypes = {};
    };

    // implemetations
    // get archetype implementation
    template <typename T, typename... types>
    std::shared_ptr<Archetype> ArchetypeManager::IGetArchetype()
    {
        Signature signature{};
        ComponentManager::GetSignature<T, types...>(signature);
        return IGetArchetype(signature);
    }

    // create archetype implementation
    template <typename T, typename... types>
    void ArchetypeManager::CreateArchetype()
    {
        Signature signature{};
        ComponentManager::GetSignature<T, types...>(signature);
        CreateArchetype(signature);
    }

} // namespace ASEngine


#endif