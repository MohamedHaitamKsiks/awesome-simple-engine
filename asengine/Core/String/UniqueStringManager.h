#ifndef ASENGINE_UNIQUE_STRING_MANAGER_H
#define ASENGINE_UNIQUE_STRING_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "Core/Error/Assertion.h"
#include "Core/Singleton/Singleton.h"

namespace ASEngine
{
    //unique string id
    using UniqueStringID = uint32_t;
    constexpr uint32_t UNIQUE_STRING_ID_NULL = UINT32_MAX;

    // unique string manager, use UniqueString type directly
    class UniqueStringManager: public Singleton<UniqueStringManager>
    {
        public:
            // create string if not found
            UniqueStringID Create(const std::string &targetString);
            
            // get length
            inline size_t GetLength(UniqueStringID stringID) const
            {   
                ASENGINE_ASSERT(stringID != UNIQUE_STRING_ID_NULL, "Cannot get length of null string");
                return m_Strings[stringID].length();
            };

            // get string
            const std::string& GetString(UniqueStringID stringID) const
            {
                ASENGINE_ASSERT(stringID != UNIQUE_STRING_ID_NULL, "Cannot get std::string of null string");
                return m_Strings[stringID];
            }

        private:
            // list of strings data
            std::vector<std::string> m_Strings{};
            std::unordered_map<std::string, UniqueStringID> m_StringIDs{};
            
            // return the id of the string if found
            UniqueStringID Find(const std::string &str);
    };
}

#endif