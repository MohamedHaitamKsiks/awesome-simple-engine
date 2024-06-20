#include "UniqueStringManager.h"

namespace ASEngine
{
    // unique string manager implementations
    UniqueStringID UniqueStringManager::Find(const std::string &targetString)
    {
        if (m_StringIDs.find(targetString) == m_StringIDs.end())
            return UNIQUE_STRING_ID_NULL;

        return m_StringIDs[targetString];
    }

    UniqueStringID UniqueStringManager::Create(const std::string &str)
    {   
        std::unique_ptr<std::string> pStr = std::make_unique<std::string>(str);

        // return index if string exists
        UniqueStringID index = Find(str);

        if (index != UNIQUE_STRING_ID_NULL)
            return index;
        
        // create new string
        UniqueStringID newIndex = static_cast<UniqueStringID>(m_Strings.size());
        
        m_Strings.push_back(std::move(pStr));
        m_StringIDs[str] = newIndex;
        
        return newIndex;
    }

} // namespace ASEngine
