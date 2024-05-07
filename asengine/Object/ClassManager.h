#ifndef ASENGINE_CLASS_MANAGER_H
#define ASENGINE_CLASS_MANAGER_H

#include <unordered_map>
#include <memory>

#include "Object.h"
#include "Class.h"
#include "Core/Error/Assertion.h"
#include "Core/String/UniqueString.h"
#include "Core/Singleton/Singleton.h"

namespace ASEngine
{
    // manages classes    
    class ClassManager: public Singleton<ClassManager>
    {
    public:

        template <typename T>
        void RegisterClass(UniqueString className)
        {
            ASENGINE_ASSERT(m_Classes.find(className) == m_Classes.end(), className.GetString() + ": Class aready registered!");
            
            Object<T>::s_ClassName = className;
            
            std::unique_ptr<Class> newClass{ new Class(className, sizeof(T)) };
            m_Classes[className] = std::move(newClass);
        }

        inline Class& GetClass(UniqueString className)
        {
            return *m_Classes[className].get();
        }
    private:
        std::unordered_map<UniqueString, std::unique_ptr<Class>> m_Classes{};
    };

} // namespace ASEngine


#endif // ASENGINE_CLASS_MANAGER_H