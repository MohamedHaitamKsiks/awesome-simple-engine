#ifndef ASENGINE_UNIQUE_STRING_MANAGER_H
#define ASENGINE_UNIQUE_STRING_MANAGER_H

#include <string>
#include <sstream>
#include <cstring>

#include "engine/Log/Log.h"
#include "engine/Memory/DynamicArray.h"
#include "engine/Memory/PoolAllocator.h"
#include "engine/Singleton/Singleton.h"

namespace ASEngine
{
    //unique string id
    using UniqueStringID = uint32_t;

    // define unique string informations
    struct UniqueStringInfo
    {
        // where the string starts
        uint32_t StartIndex = CHUNK_NULL;
        // length of the string
        size_t Length = 0;
    };

    // unique string manager, singleton that manages unique strings. 
    class UniqueStringManager: public Singleton<UniqueStringManager>
    {
        public:
            // create string if not found
            UniqueStringID Create(const std::string &str);
            // get length
            inline size_t GetLength(UniqueStringID stringID)
            {
                return m_StringInfos[stringID].Length;
            };
            // get std::string 
            std::string GetString(UniqueStringID stringId);

        private:
            // where strings data are stored
            char m_StringData[UINT16_MAX];
            size_t m_StringDataHead = 0;
            // list of strings
            TDynamicArray<UniqueStringInfo> m_StringInfos{UINT16_MAX};
            // return the id of the string if found
            UniqueStringID Find(const std::string &str);
    };
}

#endif