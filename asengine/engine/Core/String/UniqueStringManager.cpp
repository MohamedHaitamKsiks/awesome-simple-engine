#include "UniqueStringManager.h"

namespace ASEngine
{
    // unique string manager implementations
    UniqueStringID UniqueStringManager::Find(const std::string &str)
    {
        size_t strLength = str.length();
        UniqueStringID index = 0;
        
        for (auto& info: m_StringInfos)
        {
            if (info.Length != strLength)
            {
                index++;
                continue;
            }
            //check characters one by one
            bool areStringEquals = true;
            for (size_t i = 0; i < strLength; i++)
            {
                if (str[i] != m_StringData[i + info.StartIndex])
                {
                    areStringEquals = false;
                    break;
                }
            }
            //if found string return index
            if (areStringEquals)
            {
                return index;
            }
            
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
        newStrInfo.StartIndex = m_StringDataHead;

        for (size_t i = 0; i < strLength; i++) 
        {
            m_StringData[i + m_StringDataHead] = str[i];
        }
        m_StringDataHead += strLength;

        index = (UniqueStringID) m_StringInfos.Push(newStrInfo);

        return index;
    }

    std::string UniqueStringManager::GetString(UniqueStringID stringId)
    {
        UniqueStringInfo& info = m_StringInfos[stringId];
        char string[info.Length + 1];
        string[info.Length] = '\0';
        memcpy(string, m_StringData + info.StartIndex, info.Length);

        return std::string(string);
    }

} // namespace ASEngine
