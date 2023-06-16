#ifndef ASENGINE_UNIQUE_STRING_H
#define ASENGINE_UNIQUE_STRING_H

#include <string>
#include <cstdint>

/*
    unique strings are used for as references for resources.
    2 main advantages:
        1- fast comparaison
        2- efficient storing
*/
class UniqueString
{
public:
    UniqueString(size_t _length);
    UniqueString(const std::string& str);
    //compare strings
    bool operator==(const UniqueString& uStr);
    //get string length
    size_t getLength();
private:
    /* data */
    size_t length = 0;
    uint32_t id;
};



#endif