#ifndef ASENGINE_SIGNATURE_H
#define ASENGINE_SIGNATURE_H

#include "Core/String/UniqueString.h"
#include <set>

namespace ASEngine
{
    /*
    define signatuer as a set of UniqueStrings
    each UniqueString is a name of a component
    */
    using Signature = std::set<UniqueString>;
}


// define hash function for unique string
namespace std
{
    template <>
    struct hash<ASEngine::Signature>
    {
        size_t operator()(const ASEngine::Signature &x) const
        {
            uint32_t hash_combined = 0;

            for (auto e: x)
            {
                hash<uint32_t>()((uint32_t) e.GetID());
            }
            return hash_combined;
        }
    };
}

#endif // ASENGINE_SIGNATURE_H