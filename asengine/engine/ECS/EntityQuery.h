#ifndef ASENGINE_ENTITY_QUERY_H
#define ASENGINE_ENTITY_QUERY_H

#include <functional>
#include <algorithm>

#include "Core/Memory/DynamicArray.h"

#include "ComponentManager.h"
#include "Component.h"
#include "ArchetypeManager.h"
#include "Archetype.h"
#include "Signature.h"

namespace ASEngine
{
    // ecs query to get list of archetypes
    template <typename T, typename... types>
    class TEntityQuery
    {
    public:
        TEntityQuery()
        {
            // get signature
            ComponentManager::GetSignature<T, types...>(m_Signature);

            // fetch all archetypes
            const auto& archetypes = ArchetypeManager::GetArchetypes();
            for (const auto& pair: archetypes)
            {
                const auto& signature = pair.first; 
                const auto& archetype = pair.second;

                if (std::includes(signature.begin(), signature.end(), m_Signature.begin(), m_Signature.end()))
                    m_Archetypes.Push(archetype);
                
            }

        }

        // go throw every entity in the query
        void ForEach(std::function<void(T &, types &...)> callback)
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
        inline const TDynamicArray<Archetype *> &GetArchetypes() const
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
        TDynamicArray<Archetype *> m_Archetypes;
    };

} // namespace ASEngine

#endif // ASENGINE_ENTITY_QUERY_H