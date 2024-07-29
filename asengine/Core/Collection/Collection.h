#ifndef __ASENGINE_COLLECTION_H
#define __ASENGINE_COLLECTION_H

#include <cstdint>


namespace ASEngine
{
    // interface for collection
    class  ICollection
    {
    public:
        virtual ~ICollection() {}

        virtual uint32_t Add() = 0;

        virtual void Remove(uint32_t index) = 0;

        virtual size_t GetSize() const = 0;
    };
} // namespace ASEngine


#endif // __ASENGINE
