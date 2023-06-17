#include "UniqueStringManager.h"

namespace ASEngine
{
    // singleton implementations
    UniqueStringManager* UniqueStringManager::uniqueStringManager = nullptr;

    void UniqueStringManager::init()
    {
        if (!uniqueStringManager)
            uniqueStringManager = new UniqueStringManager();
    }

    UniqueStringManager* UniqueStringManager::getSingleton()
    {
        return uniqueStringManager;
    }

    void UniqueStringManager::terminate()
    {
        if (uniqueStringManager)
            delete uniqueStringManager;
    }


    // unique string manager implementations
    UniqueStringID UniqueStringManager::find(const std::string &str)
    {
        size_t strLength = str.length();
        
        UniqueStringID index = 0;
        
        for (UniqueStringInfo* info: stringInfos)
        {
            if (info->length != strLength)
                continue;
            //check characters one by one
            bool areStringEquals = true;

            PoolAllocator<char>::Iterator it = PoolAllocator<char>::Iterator(&stringData, info->startIndex);
            for (int i = 0; i < strLength && it != stringData.end(); i++)
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
        return CHUNK_ID_NULL;
    }

    UniqueStringID UniqueStringManager::create(const std::string &str)
    {
        UniqueStringID index = find(str);
        if (index != UINT32_MAX)
            return index;
        
        //create new string
        size_t strLength = str.length();
        //new string info
        UniqueStringInfo newStrInfo;
        newStrInfo.length = strLength;

        for (int i = 0; i < strLength; i++) 
        {
            ChunkId charId = stringData.alloc();
            *stringData.get(charId) = str[i];
            if (i == 0)
                newStrInfo.startIndex = charId;
            
        }

        index = (UniqueStringID) stringInfos.alloc();
        *stringInfos.get((ChunkId) index) = newStrInfo;

        return index;
    }

    size_t UniqueStringManager::getLength(UniqueStringID stringId)
    {
        return stringInfos.get(stringId)->length;
    }

    std::string UniqueStringManager::getString(UniqueStringID stringId)
    {
        std::stringstream ss;
        UniqueStringInfo* info = stringInfos.get(stringId);

        PoolAllocator<char>::Iterator it = PoolAllocator<char>::Iterator(&stringData, info->startIndex);
        for (int i = 0; i < info->length && it != stringData.end(); i++)
        {
            ss << *(*it);
            it++;
        }

        return ss.str();
    }

} // namespace ASEngine
