#ifndef __ASENGINE_COMPONENT_CLASS_H
#define __ASENGINE_COMPONENT_CLASS_H

#include "Core/String/UniqueString.h"
#include "Core/Singleton/Singleton.h"
#include "Component.h"
#include "ComponentCollection.h"
#include "Class/Class.h"
#include "Class/ClassManager.h"

#include "API/API.h"

namespace ASEngine
{
    class ASENGINE_API IComponentClass
    {
    public:
        virtual AbstractComponent* New() = 0; 

        virtual IComponentCollection* CreateComponentCollection() = 0;
    };


    template <typename T>
    class ASENGINE_API ComponentClass: public IComponentClass
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


#endif // __ASENGINE_COMPONENT_CLASS_H