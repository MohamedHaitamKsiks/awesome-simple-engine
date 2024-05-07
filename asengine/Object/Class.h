#ifndef ASENGINE_CLASS_H
#define ASENGINE_CLASS_H

#include "Core/String/UniqueString.h"

namespace ASEngine
{
    // abstarct class implemented as template
    class Class
    {
    public:
        // don't allow copy
        Class(const Class&) = delete;
        Class& operator=(const Class&) = delete;

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

    private:
        Class(UniqueString name, size_t size);
        friend class ClassManager;
    };
} // namespace ASEngine


#endif // ASENGINE_CLASS_H