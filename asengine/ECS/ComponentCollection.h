#ifndef __ASENGINE_COMPONENT_COLLECTION_H
#define __ASENGINE_COMPONENT_COLLECTION_H

#include <vector>
#include "Component.h"
#include "Core/Collection/Collection.h"



namespace ASEngine
{
    // component index in the collection
    using ComponentIndex = uint32_t;

    // interface of component collection behaviour
    class  IComponentCollection : public ICollection
    {
    public:
        virtual ~IComponentCollection() {}

        virtual AbstractComponent& ComponentAt(ComponentIndex index) = 0;

        virtual const AbstractComponent& ComponentAt(ComponentIndex index) const = 0 ;

        // only keep component in these indicies
        virtual void KeepOnly(const std::vector<ComponentIndex> indices) = 0;
    };


    // template of component collection
    template <typename ComponentType>
    class ComponentCollection : public IComponentCollection
    {
    public:
        ComponentCollection()
        {
            static_assert(std::is_base_of_v<Component<ComponentType>, ComponentType>);
            m_Components.reserve(UINT16_MAX);
        }

        ~ComponentCollection()
        {}

        ComponentIndex Add() override
        {
            m_Components.emplace_back();
            return static_cast<ComponentIndex>(m_Components.size() - 1);
        };

        ComponentIndex Add(const ComponentType& component)
        {
            m_Components.push_back(component);
            return static_cast<ComponentIndex>(m_Components.size() - 1);
        }

        void Remove(ComponentIndex index) override
        {
            m_Components.erase(m_Components.cbegin() + index);
        }

        void KeepOnly(const std::vector<ComponentIndex> indices) override
        {
            ComponentIndex currentIndex = 0;
            for (const auto& index: indices)
            {
                if (index != currentIndex && index < m_Components.size())
                {
                    m_Components[currentIndex] = m_Components[index];
                }

                currentIndex++;
            }

            m_Components.resize(indices.size());
        }

        size_t GetSize() const override
        {
            return m_Components.size();
        }

        AbstractComponent &ComponentAt(ComponentIndex index) override
        {
            return m_Components[index];
        }

        const AbstractComponent &ComponentAt(ComponentIndex index) const override
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


#endif // __ASENGINE_COMPONENT_COLLECTION_H
