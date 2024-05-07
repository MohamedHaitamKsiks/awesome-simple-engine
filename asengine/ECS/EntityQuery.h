#ifndef ASENGINE_ENTITY_QUERY_H
#define ASENGINE_ENTITY_QUERY_H

#include <functional>
#include <algorithm>
#include <vector>

#include "ComponentManager.h"
#include "Component.h"
#include "ArchetypeManager.h"
#include "Archetype.h"
#include "Signature.h"

#include "Macros/Foreach.h"

#define ASENGINE_ENTITY_QUERY_FOREACH_BEGIN(query, ...) \
for (Archetype * archetype : query.GetArchetypes()) \
{ \
    FOREACH(GET_COMPONENT_COLLECTION, __VA_ARGS__) \
    for (ComponentIndex index = 0; index < archetype->GetSize(); index++) \
    { \
        FOREACH(GET_COMPONENT_AT_INDEX, __VA_ARGS__)

#define ASENGINE_ENTITY_QUERY_FOREACH_END() \
    } \
}

#define GET_COMPONENT_COLLECTION(ComponentType) auto& collectionOf ## ComponentType = archetype->GetComponentCollection<ComponentType>();
#define GET_COMPONENT_AT_INDEX(ComponentType) auto &current ## ComponentType = collectionOf ## ComponentType[index];

namespace ASEngine
{
    // ecs query to get list of archetypes
    // all entities will be queried in construction
    template <typename T, typename... types>
    class EntityQuery
    {
    public:
        EntityQuery()
        {
            // get signature
            ComponentManager::GetSignature<T, types...>(m_Signature);

            // fetch all archetypes
            auto& archetypes = ArchetypeManager::GetInstance().GetArchetypes();
            for (auto& [signature, archetype]: archetypes)
            {
                if (std::includes(signature.begin(), signature.end(), m_Signature.begin(), m_Signature.end()))
                    m_Archetypes.push_back(&archetype);
                
            }

        }

        // go throw every entity in the query
        template<typename FunctionType>
        void ForEach(FunctionType callback)
        {
            for (auto& archetype : m_Archetypes)
            {
                ComponentCollection<T> &collection = archetype->template GetComponentCollection<T>();
                std::tuple<ComponentCollection<types> &...> collections(archetype->template GetComponentCollection<types>()...);

                for (ComponentIndex i = 0; i < collection.GetSize(); i++)
                {
                    std::apply([callback, &collection, &i] (ComponentCollection<types> &...collections)
                    { 
                        callback(collection[i], collections[i]...); 
                    }, collections);
                }
            }
        };

        // get archetypes
        inline const std::vector<Archetype*> &GetArchetypes() const
        {
            return m_Archetypes;
        };

        // get signature
        inline const Signature &GetSignature() const
        {
            return m_Signature;
        };

    private:
        Signature m_Signature;
        std::vector<Archetype*> m_Archetypes;
    };

} // namespace ASEngine

#endif // ASENGINE_ENTITY_QUERY_H