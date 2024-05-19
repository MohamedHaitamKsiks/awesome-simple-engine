#ifndef ASENGINE_COMPONENT_CLASS_H
#define ASENGINE_COMPONENT_CLASS_H

#include "Core/String/UniqueString.h"
#include "Core/Singleton/Singleton.h"
#include "Component.h"
#include "ComponentCollection.h"
#include "Class/Class.h"
#include "Class/ClassManager.h"

namespace ASEngine
{
    class IComponentClass
    {
    public:
        virtual AbstractComponent* New() = 0; 

        virtual IComponentCollection* CreateComponentCollection() = 0;
    };


    template <typename T>
    class ComponentClass: public IComponentClass
    {
    public:
        AbstractComponent* New() override 
        {
            return new T();
        }

        IComponentCollection* CreateComponentCollection() override
        {
            return new ComponentCollection<T>();
        }
    };
} // namespace ASEngine


#endif // ASENGINE_COMPONENT_CLASS_H