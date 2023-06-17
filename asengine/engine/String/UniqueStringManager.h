#ifndef ASENGINE_UNIQUE_STRING_MANAGER_H
#define ASENGINE_UNIQUE_STRING_MANAGER_H

#include <string>
#include <sstream>
#include <cstring>

#include "../Log/Log.h"
#include "../Memory/PoolAllocator.h"

namespace ASEngine
{
    //unique string id
    typedef uint32_t UniqueStringID;

    // define unique string informations
    struct UniqueStringInfo
    {
        // where the string starts
        ChunkId startIndex;
        // length of the string
        size_t length = 0;
    };

    // unique string manager, singleton that manages unique strings. 
    class UniqueStringManager 
    {
        public:
            // init 
            static void init();
            static UniqueStringManager* getSingleton();
            static void terminate();
            // create string if not found
            UniqueStringID create(const std::string &str);
            // get length
            size_t getLength(UniqueStringID stringId);
            // get std::string 
            std::string getString(UniqueStringID stringId);

        private:
            // singleton
            static UniqueStringManager* uniqueStringManager;
            // where strings data are stored
            PoolAllocator<char> stringData{UINT16_MAX};
            // list of strings
            PoolAllocator<UniqueStringInfo> stringInfos{UINT16_MAX};
            // return the id of the string if found
            UniqueStringID find(const std::string &str);
    };
}

#endif