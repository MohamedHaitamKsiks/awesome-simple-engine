#include "EntityQueryBase.h"
#include "ArchetypeManager.h"

namespace ASEngine
{
    EntityQueryBase::EntityQueryBase(const Signature &signature)
    {
        m_Signature = signature;

        // fetch all archetypes that intersects with signature
        auto &archetypes = ArchetypeManager::GetInstance().GetArchetypes();
        for (auto &[signature, archetype] : archetypes)
        {
            if (std::includes(signature.begin(), signature.end(), m_Signature.begin(), m_Signature.end()))
                m_Archetypes.push_back(&archetype);
        }
    }

    EntityQueryBase::~EntityQueryBase()
    {
    }

} // namespace ASEngine
