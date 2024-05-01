#ifndef ASENGINE_UNIQUE_STRING_H
#define ASENGINE_UNIQUE_STRING_H

#include <functional>
#include <string>

#include "UniqueStringManager.h"

namespace ASEngine
{

    /*
        unique strings are used for as references for resources.
        2 main advantages:
            1- fast comparaison
            2- efficient storing
    */
    class UniqueString
    {
    public:
        UniqueString();

        // create unique string from given str, if str exists it will have the same id. 
        UniqueString(const std::string& str);

        // compare strings
        friend inline bool operator<(const UniqueString &uStrLeft, const UniqueString &uStrRight)
        {
            return uStrLeft.m_StringID < uStrRight.m_StringID;
        };

        friend inline bool operator==(const UniqueString& uStrLeft, const UniqueString& uStrRight)
        {
            return uStrLeft.m_StringID == uStrRight.m_StringID;
        };

        friend inline bool operator!=(const UniqueString &uStrLeft, const UniqueString &uStrRight)
        {
            return uStrLeft.m_StringID != uStrRight.m_StringID;
        };

        // get string length
        inline size_t GetLength() const
        {
            return UniqueStringManager::GetInstance().GetLength(m_StringID);
        }

        // get id
        inline UniqueStringID GetID() const 
        { 
            return m_StringID; 
        };

        // get std::string from this string use it only for debug and log
        inline const std::string& GetString() const 
        {
            return UniqueStringManager::GetInstance().GetString(m_StringID);
        };

    private:
        /* data */
        UniqueStringID m_StringID = UNIQUE_STRING_ID_NULL;

        // create a unique string from std::string
        inline void Create(const std::string& str)
        {
            m_StringID = UniqueStringManager::GetInstance().Create(str);
        }

    };

} // namespace ASEngine

// define hash function for unique string
namespace std
{
    template <> 
    struct hash<ASEngine::UniqueString>
    {
        size_t operator()(const ASEngine::UniqueString &x) const
        {
            return hash<uint32_t>()(static_cast<uint32_t>(x.GetID()));
        }
    };
}

#endif