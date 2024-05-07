#ifndef ASENGINE_COMPONENT_COLLECTION_H
#define ASENGINE_COMPONENT_COLLECTION_H

#include <vector>
#include "Component.h"
#include "Core/Collection/Collection.h"

namespace ASEngine
{
    // component index in the collection
    using ComponentIndex = uint32_t;

    // interface of component collection behaviour
    class IComponentCollection: public ICollection
    {
    public:
        virtual IComponent& ComponentAt(ComponentIndex index) = 0;
        
        virtual const IComponent& ComponentAt(ComponentIndex index) const = 0 ;
    };


    // template of component collection
    template<typename ComponentType>
    class ComponentCollection: public IComponentCollection
    {
    public:
        ComponentCollection()
        {
            static_assert(std::is_base_of_v<Component<ComponentType>, ComponentType>);
            m_Components.reserve(UINT16_MAX);
        }

        ComponentIndex Add()
        {
            ComponentType component{};
            m_Components.push_back(component);
            return static_cast<ComponentIndex>(m_Components.size() - 1);
        };

        ComponentIndex Add(const ComponentType& component)
        {
            m_Components.pop_back(component);
            return static_cast<ComponentIndex>(m_Components.size() - 1);
        }

        void Remove(ComponentIndex index)
        {
            m_Components.erase(m_Components.cbegin() + index);
        }

        size_t GetSize() const
        {
            return m_Components.size();
        }

        IComponent &ComponentAt(ComponentIndex index)
        {
            return m_Components[index];
        }
        
        const IComponent &ComponentAt(ComponentIndex index) const
        {
            return m_Components[index];
        }

        inline ComponentType &operator[](ComponentIndex index)
        {
            return m_Components[index];
        }

        inline const ComponentType &operator[](ComponentIndex index) const
        {
            return m_Components[index];
        }

        // iterator
        using Iterator = std::vector<ComponentType>::iterator;

        Iterator begin() const
        {
            return m_Components.begin();
        }

        Iterator end() const
        {
            return m_Components.end();
        }

    private:
        std::vector<ComponentType> m_Components{};
    };


} // namespace ASEngine


#endif // ASENGINE_COMPONENT_COLLECTION_H