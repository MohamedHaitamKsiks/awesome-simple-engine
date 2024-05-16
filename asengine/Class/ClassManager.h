#ifndef ASENGINE_CLASS_MANAGER_H
#define ASENGINE_CLASS_MANAGER_H

#include <unordered_set>
#include <memory>

#include "Class.h"
#include "Core/Error/Assertion.h"
#include "Core/String/UniqueString.h"
#include "Core/Singleton/Singleton.h"

namespace ASEngine
{
    // manages classes    
    class ClassManager
    {
    ASENGINE_DEFINE_SINGLETON(ClassManager);
    
    public:

        template <typename T>
        void RegisterClass(UniqueString className)
        {
            ASENGINE_ASSERT(m_Classes.find(className) == m_Classes.end(), className.GetString() + ": Type aready registered!");
            
            Class<T>::s_ClassName = className;
            m_Classes.insert(className);
        }

    private:
        std::unordered_set<UniqueString> m_Classes{};
    };

} // namespace ASEngine


#endif // ASENGINE_CLASS_MANAGER_H