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
        UniqueString(UniqueStringID id);
        // empty constructor
        UniqueString() {};

        // compare strings
        friend inline bool operator<(const UniqueString &uStrLeft, const UniqueString &uStrRight)
        {
            return uStrLeft.m_Id < uStrRight.m_Id;
        };

        friend inline bool operator==(const UniqueString& uStrLeft, const UniqueString& uStrRight)
        {
            return uStrLeft.m_Id == uStrRight.m_Id;
        };

        friend inline bool operator!=(const UniqueString &uStrLeft, const UniqueString &uStrRight)
        {
            return uStrLeft.m_Id != uStrRight.m_Id;
        };
        // get string length
        inline size_t GetLength() const
        {
            return UniqueStringManager::GetSingleton()->GetLength(m_Id);
        }
        // get id
        inline UniqueStringID GetId() const 
        { 
            return m_Id; 
        };
        // get std::string from this string use it only for debug and log
        inline std::string GetString() const 
        { 
            return UniqueStringManager::GetSingleton()->GetString(m_Id); 
        };

    private:
        /* data */
        UniqueStringID m_Id = CHUNK_NULL;
    };

    const UniqueString UNIQUE_STRING_NULL = UniqueString(CHUNK_NULL);

} // namespace ASEngine

// define hash function for unique string
namespace std
{
    template <>
    struct hash<ASEngine::UniqueString>
    {
        size_t operator()(const ASEngine::UniqueString &x) const
        {
            return hash<uint32_t>()((uint32_t) x.GetId());
        }
    };
}

#endif