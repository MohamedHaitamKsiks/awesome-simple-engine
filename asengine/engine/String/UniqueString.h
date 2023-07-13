#ifndef ASENGINE_UNIQUE_STRING_H
#define ASENGINE_UNIQUE_STRING_H

#include <string>
#include "UniqueStringManager.h"

/*
    unique strings are used for as references for resources.
    2 main advantages:
        1- fast comparaison
        2- efficient storing
*/

#define UNIQUE_STRING_ID_NULL UINT32_MAX;

namespace ASEngine
{

    class UniqueString
    {
    public:
        // create unique string from given str, if str exists it will have the same id. 
        UniqueString(const std::string& str);
        // create from id
        UniqueString(UniqueStringID _id);
        // empty constructor
        UniqueString() {};
        // compare strings
        bool operator==(const UniqueString& uStr);
        // get string length
        size_t getLength() const;
        // get id
        UniqueStringID getId() const;
        // get std::string from this string use it only for debug and log 
        std::string getString() const;
    private:
        /* data */
        UniqueStringID id = UINT32_MAX;
    };
} // namespace ASEngine


#endif