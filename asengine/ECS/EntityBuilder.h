#ifndef __ASENGINE_ENTITY_BUILDER_H
#define __ASENGINE_ENTITY_BUILDER_H

#include <memory>
#include <unordered_map>

#include "Core/String/UniqueString.h"
#include "Core/String/UniqueStringManager.h"
#include "Component.h"
#include "Signature.h"
#include "Archetype.h"


namespace ASEngine
{
    // builder to create a new entity
    class  EntityBuilder
    {
        public:
            EntityBuilder() {};

            // copy constructor
            EntityBuilder(const EntityBuilder& builder);

            EntityBuilder& operator=(const EntityBuilder& builder);

            // add component with no initial value
            void AddComponent(UniqueString componentName);

            // set component with inital value
            void AddComponent(UniqueString componentName, const AbstractComponent& component);

            // add component based on type
            template <typename T, typename... types>
            void AddComponents(const T& firstComponent, const types&... components)
            {
                UniqueString componentName = Component<T>::GetName();
                AddComponent(componentName, firstComponent);

                if constexpr(sizeof...(types) > 0)
                {
                    AddComponents(components...);
                }
            }

            // get components
            inline const std::map<UniqueString, std::unique_ptr<AbstractComponent>>& GetComponents() const
            {
                return m_Components;
            }

            // get component
            inline AbstractComponent& GetComponent(UniqueString componentName)
            {
                return *m_Components[componentName];
            }

            // get component by types
            template<typename T>
            inline T& GetComponent()
            {
                return static_cast<T&>(*m_Components[Component<T>::GetName()]);
            }

            // get signature
            const Signature& GetSignature() const
            {
                return m_Signature;
            }

            inline void SetPersistant(bool persistant)
            {
                m_Persistent = persistant;
            }

            inline bool IsPersistant() const
            {
                return m_Persistent;
            }

            // set entity tag
            inline void SetTag(UniqueString tag)
            {
                m_Tag = tag;
            }

            // get entity tag
            inline UniqueString GetTag() const
            {
                return m_Tag;
            }

            // check if builder tag is defined
            inline bool HasTag() const
            {
                return m_Tag.GetID() != UNIQUE_STRING_ID_NULL;
            }

        private:
            std::map<UniqueString, std::unique_ptr<AbstractComponent>> m_Components{};
            void Copy(const EntityBuilder& builder);

            // cache signatrue
            Signature m_Signature{};
            Archetype* m_Archetype = nullptr;
            UniqueString m_Tag{};

            // is entity going to be kept when changing scene
            bool m_Persistent = false;

            friend class EntityManager;
    };

} // namespace ASEngine


#endif // __ASENGINE_ENTITY_BUILDER_H
