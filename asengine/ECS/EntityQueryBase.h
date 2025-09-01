#ifndef __ASENGINE_ENTITY_QUERY_BASE_H
#define __ASENGINE_ENTITY_QUERY_BASE_H

#include "Signature.h"
#include "Archetype.h"

#include <vector>

namespace ASEngine
{
    // base class for entity query
    class EntityQueryBase
    {
    public:
        EntityQueryBase(const Signature& signature);
        ~EntityQueryBase();

        // get archetypes
        inline const std::vector<Archetype *> &GetArchetypes() const
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


#endif // __ASENGINE_ENTITY_QUERY_BASE_H