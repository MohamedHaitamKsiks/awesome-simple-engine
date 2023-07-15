#ifndef ASENGINE_UNIQUE_STRING_MANAGER_H
#define ASENGINE_UNIQUE_STRING_MANAGER_H

#include <string>
#include <sstream>
#include <cstring>

#include "../Log/Log.h"
#include "../Memory/PoolAllocator.h"
#include "../Singleton/Singleton.h"

namespace ASEngine
{
    //unique string id
    using UniqueStringID = uint32_t;

    // define unique string informations
    struct UniqueStringInfo
    {
        // where the string starts
        ChunkID startIndex;
        // length of the string
        size_t length = 0;
    };

    // unique string manager, singleton that manages unique strings. 
    class UniqueStringManager: public Singleton<UniqueStringManager>
    {
        public:
            // create string if not found
            UniqueStringID create(const std::string &str);
            // get length
            size_t getLength(UniqueStringID stringId);
            // get std::string 
            std::string getString(UniqueStringID stringId);

        private:
            // where strings data are stored
            PoolAllocator<char> stringData{UINT16_MAX};
            // list of strings
            PoolAllocator<UniqueStringInfo> stringInfos{UINT16_MAX};
            // return the id of the string if found
            UniqueStringID find(const std::string &str);
    };
}

#endif