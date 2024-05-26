#ifndef __ASENGINE_ARCHETYPE_MANAGER_H
#define __ASENGINE_ARCHETYPE_MANAGER_H

#include <unordered_map>
#include <memory>
#include <set>

#include "Core/Singleton/Singleton.h"

#include "Archetype.h"
#include "Signature.h"

#include "System.h"

namespace ASEngine
{
    class ArchetypeManager: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(ArchetypeManager);

    public:
        // get archetype 
        template <typename T, typename... types>
        Archetype& GetArchetype()
        {
            Signature signature{};
            ComponentManager::GetSignature<T, types...>(signature);
            return GetArchetype(signature);
        }

        // get archetype by signature
        Archetype& GetArchetype(const Signature& signature);

        // get all registered archetypes
        inline std::unordered_map<Signature, Archetype>& GetArchetypes()
        {
            return m_Archetypes;
        }

    private:
        // create archetype based on list of component names
        void CreateArchetype(const Signature& signature);

        // has signature
        bool HasArchetype(const Signature& signature) const;

        // map signature to corresponding archetype
        std::unordered_map<Signature, Archetype> m_Archetypes = {};
    };


} // namespace ASEngine


#endif