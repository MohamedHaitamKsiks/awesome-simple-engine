#include "UniqueStringManager.h"

namespace ASEngine
{
    // unique string manager implementations
    UniqueStringID UniqueStringManager::Find(const std::string &str)
    {
        size_t strLength = str.length();
        
        UniqueStringID index = 0;
        
        for (UniqueStringInfo* info: m_StringInfos)
        {
            if (info->Length != strLength)
            {
                index++;
                continue;
            }
            //check characters one by one
            bool areStringEquals = true;

            PoolAllocator<char>::Iterator it = PoolAllocator<char>::Iterator(&m_StringData, info->StartIndex);

            for (size_t i = 0; i < strLength && it != m_StringData.end(); i++)
            {
                if (str[i] != *(*it))
                {
                    areStringEquals = false;
                    break;
                }
                it++;
            }
            //if found string return index
            if (areStringEquals)
                return index;
            
            index++;
        }
        
        //return null if not found
        return CHUNK_NULL;
    }

    UniqueStringID UniqueStringManager::Create(const std::string &str)
    {
        UniqueStringID index = Find(str);
        if (index != CHUNK_NULL)
            return index;
        
        //create new string
        size_t strLength = str.length();
        //new string info
        UniqueStringInfo newStrInfo;
        newStrInfo.Length = strLength;

        for (size_t i = 0; i < strLength; i++) 
        {
            ChunkID charId = m_StringData.Alloc();
            *m_StringData.Get(charId) = str[i];
            if (i == 0)
                newStrInfo.StartIndex = charId;
            
        }

        index = (UniqueStringID)m_StringInfos.Push(newStrInfo);

        return index;
    }

    std::string UniqueStringManager::GetString(UniqueStringID stringId)
    {
        std::stringstream ss;
        UniqueStringInfo* info = m_StringInfos.Get(stringId);

        PoolAllocator<char>::Iterator it = PoolAllocator<char>::Iterator(&m_StringData, info->StartIndex);
        for (size_t i = 0; i < info->Length && it != m_StringData.end(); i++)
        {
            ss << *(*it);
            it++;
        }

        return ss.str();
    }

} // namespace ASEngine
