#ifndef ASENGINE_COMPONENT_CLASS_H
#define ASENGINE_COMPONENT_CLASS_H

#include "Core/String/UniqueString.h"
#include "Core/Singleton/Singleton.h"
#include "Component.h"
#include "ComponentCollection.h"
#include "Object/Class.h"
#include "Object/ClassManager.h"

namespace ASEngine
{
    class ComponentClass
    {
    public:
        ComponentClass(UniqueString componentName);
        
        inline Class& GetClass()
        {
            return ClassManager::GetInstance().GetClass(m_ComponentName);
        }

        virtual IComponentCollection* CreateComponentCollection() = 0;
    private:
        UniqueString m_ComponentName;
    };


    template <typename T>
    class TComponentClass: public ComponentClass, public Singleton<TComponentClass<T>> 
    {
    public:
        IComponentCollection* CreateComponentCollection() override
        {
            return ComponentCollection<T>::GetClass().New();
        }
    };
} // namespace ASEngine


#endif // ASENGINE_COMPONENT_CLASS_H