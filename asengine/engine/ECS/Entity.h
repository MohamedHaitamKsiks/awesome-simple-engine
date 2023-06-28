#ifndef ASENGINE_ENTITY_H
#define ASENGINE_ENTITY_H

#include <vector>
#include <cstdint>
#include "../String/UniqueString.h"

namespace ASEngine
{
    // entity id
    typedef uint32_t EntityID;

    //entity class, it's just the id for the entity no need to use references to pass around an entity
    class Entity 
    {
        public:
            // contructor for entity
            Entity(EntityID _id);

            // get entity id
            EntityID getId() const;
           
            // add component
            template <typename T>
            void addComponent<T>();
            // get component 
            template <typename T>
            void getComponent<T>();
            // remove component
            template <typename T>
            void removeComponent<T>();

        private:
            // entity id
            EntityID id;

    };
    
} // namespace ASEngine


#endif