#ifndef ASENGINE_SIGNATURE_H
#define ASENGINE_SIGNATURE_H

#include "Core/String/UniqueString.h"
#include <set>

namespace ASEngine
{
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
                hash<uint32_t>()((uint32_t) e.GetId());
            }
            return hash_combined;
        }
    };
}

#endif // ASENGINE_SIGNATURE_H