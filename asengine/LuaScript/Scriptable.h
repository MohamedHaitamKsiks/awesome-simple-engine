#ifndef __ASENGINE_SCRIPTABLE_H
#define __ASENGINE_SCRIPTABLE_H

#include <memory>
#include <unordered_map>

#include "Core/Serialization/Serializer.h"

#include "Core/String/UniqueString.h"

#include "ECS/Entity.h"
#include "ECS/Component.h"

namespace ASEngine
{
    // entity scriptable component
    class Scriptable: public Component<Scriptable>
    {
    public:
        Scriptable() = default;
        ~Scriptable() {}

        inline EntityID GetOwnerID() const
        {
            return m_OwnerID;
        }

        void AddScript(UniqueString script);

    private:
        EntityID m_OwnerID = CHUNK_NULL;

        void OnCreate(EntityID ownerID) override;
        void OnDestroy() override;
    };


} // namespace ASEngine


#endif // __ASENGINE_SCRIPTABLE_H
