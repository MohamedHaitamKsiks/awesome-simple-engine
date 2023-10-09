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
    class ArchetypeManager: public Singleton<ArchetypeManager>
    {
    public:
        // destructor
        ~ArchetypeManager();

        // get archetype 
        template <typename T, typename... types>
        static inline Archetype* GetArchetype() 
        { 
            return GetSingleton()->IGetArchetype<T, types...>(); 
        }

        // get archetype by signature
        static inline Archetype* GetArchetype(const Signature& signature) 
        { 
            return GetSingleton()->IGetArchetype(signature); 
        }
        
        // get all registered archetypes
        static inline const std::unordered_map<Signature, Archetype*>& GetArchetypes()
        {
            return GetSingleton()->m_Archetypes;
        };

    private:
        // get archetype internal
        template <typename T, typename... types>
        Archetype* IGetArchetype();

        // get archetype by list of component names internal
        Archetype* IGetArchetype(const Signature& signature);

        // create archetype
        template <typename T, typename... types>
        void CreateArchetype();

        // create archetype based on list of component names
        void CreateArchetype(const Signature& signature);

        // has signature
        bool HasArchetype(const Signature& signature) const;

        // map signature to corresponding archetype
        std::unordered_map<Signature, Archetype*> m_Archetypes = {};
    };

    // implemetations
    // get archetype implementation
    template <typename T, typename... types>
    Archetype* ArchetypeManager::IGetArchetype()
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