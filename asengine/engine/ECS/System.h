#ifndef ASENGINE_SYSTEM_H
#define ASENGINE_SYSTEM_H

#include <memory>
#include <functional>
#include <vector>
#include <tuple>

#include "engine/Renderer/Graphics.h"

#include "Archetype.h"
#include "Component.h"
#include "ComponentManager.h"

namespace ASEngine
{
    // base system class
    class BaseSystem
    {
    public:
        // archetypes list
        std::vector<std::weak_ptr<Archetype>> archetypes = {};

        // get signature
        uint32_t getSignature() const
        {
            return signature;
        };

        // on update
        virtual void onUpdate(float delta) = 0;

        // on draw
        virtual void onDraw(Graphics &graphics) = 0;

    protected:
        // system signature with it's component requirements
        uint32_t signature = 1;
    };


    // system interaface
    template <typename T, typename... types>
    class System: public BaseSystem
    {
    public:
        // constructor
        System() 
        {
            signature = ComponentManager::getSingleton()->getSignature<T, types...>();
        };

        // foreach entiy with signature of system
        void forEach(std::function<void(T*, types*...)> callback)
        {
            for (auto archetype: archetypes)
            {
                ComponentCollection<T>& collection = archetype.lock()->template getComponentCollection<T>();

                for (auto it = collection.begin(); it != collection.end(); it++)
                {   
                    ChunkID index = it.currentPosition;
                    callback(collection.get(index), archetype.lock()->template getComponentCollection<types>().get(index)...);
                }
                
            }
        };

        // 
    };

} // namespace ASEngine


#endif
