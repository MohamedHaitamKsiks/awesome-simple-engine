#ifndef __ASENGINE_ENTITY_QUERY_H
#define __ASENGINE_ENTITY_QUERY_H

#include <functional>
#include <algorithm>
#include <vector>

#include "ComponentManager.h"
#include "Component.h"
#include "ArchetypeManager.h"
#include "Archetype.h"
#include "Signature.h"

#include "Macros/Foreach.h"


namespace ASEngine
{
    // ecs query to get list of archetypes
    // all entities will be queried in construction
    template <typename T, typename... types>
    class  EntityQuery
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

                for (ComponentIndex i = 0; i < archetype->GetSize(); i++)
                {
                    std::apply([callback, &collection, &i] (ComponentCollection<types> &...collections)
                    { 
                        callback(collection[i], collections[i]...); 
                    }, collections);
                }
            }
        }

        // for each component collections (please use this for better performances)
        template <typename FunctionType>
        void ForEachCollection(FunctionType callback)
        {
            for (auto& archetype : m_Archetypes)
            {
                ComponentCollection<T> &collection = archetype->template GetComponentCollection<T>();
                std::tuple<ComponentCollection<types> &...> collections(archetype->template GetComponentCollection<types>()...);
                size_t componentsCount = collection.GetSize();

                std::apply([callback, &collection, &componentsCount] (ComponentCollection<types> &...collections)
                { 
                    callback(collection, collections..., componentsCount); 
                }, collections);
                
            }
        }

        // get archetypes
        inline const std::vector<Archetype*> &GetArchetypes() const
        {
            return m_Archetypes;
        }

        // get signature
        inline const Signature &GetSignature() const
        {
            return m_Signature;
        }

    private:
        Signature m_Signature;
        std::vector<Archetype*> m_Archetypes;
    };

} // namespace ASEngine

#endif // __ASENGINE_ENTITY_QUERY_H