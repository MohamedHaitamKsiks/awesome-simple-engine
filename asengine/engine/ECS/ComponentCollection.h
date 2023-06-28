#ifndef ASENGINE_COMPONENT_COLLECTION_H
#define ASENGINE_COMPONENT_COLLECTION_H

#include "Component.h"
#include "../Memory/PoolAllocator.h"

namespace ASEngine
{

    template <typename T>
    class ComponentCollection
    {
    public:
        // init singleton
        static void init();
        // get singleton
        static ComponentCollection* getSingleton();
        // terminate singleton
        static void terminate();

        // add entity to collection
        void add(Entity owner);

        // remove component from collection
        void remove(ComponentID componentId);

        // get component by id
        Component* get(ComponentID componentId);

        // get component by owner
        Component* getByOwner(Entity owner);

    private:
        // singleton
        static ComponentCollection<T>* componentCollection;
        // list of components
        PoolAllocator<T> components{UINT16_MAX};
    }

} // namespace ASEngine



#endif