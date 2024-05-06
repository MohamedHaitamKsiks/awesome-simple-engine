#ifndef ASENGINE_CLASS_H
#define ASENGINE_CLASS_H

#include "Core/String/UniqueString.h"
#include "Object.h"

namespace ASEngine
{
    // abstarct class implemented as template
    class Class
    {
    public:
        Class(UniqueString name);

        // create new instance of class
        virtual Object* New() = 0;

        // destroy instance of class
        virtual void Destroy(Object*) = 0;
        
        // get class name
        inline UniqueString GetName() const 
        {
            return m_Name;
        }
        
        // get class size
        inline size_t GetSize() const
        {
            return m_Size;
        }

    protected:
        UniqueString m_Name;
        size_t m_Size = 0;
    };
} // namespace ASEngine


#endif // ASENGINE_CLASS_H