#ifndef ASENGINE_COMPONENT_MANAGER_H
#define ASENGINE_COMPONENT_MANAGER_H

#include <memory>
#include <cstdint>
#include <type_traits>
#include <unordered_map>

#include "Core/Serialization/Serializer.h"
#include "Core/Singleton/Singleton.h"

#include "Component.h"
#include "Signature.h"


namespace ASEngine
{
    // component collection vector for now
    template <typename T>
    using ComponentCollection = TDynamicArray<T>;
    using BaseComponentCollection = DynamicArray;

    // component information used by component manager
    struct ComponentInfo
    {
        UniqueString Name;
        size_t Size = 0;
        std::shared_ptr<BaseComponentCollection> (*CreateComponentCollection)();
        Json (*Serialize)(const Component*);
        void (*Deserialize)(const Json&, Component*);
        Component* (*MakeComponent)(const Component*);
        void (*DeleteComponent) (Component*);
        void (*CopyComponent)(Component*, const Component*);
    };

    // singleton that manages components
    class ComponentManager: public Singleton<ComponentManager>
    {
    public:
        // register component
        template <typename T>
        static inline void RegisterComponent(UniqueString componentName) { GetSingleton()->IRegisterComponent<T>(componentName); };

        // create component collection
        template <typename T>
        static std::shared_ptr<BaseComponentCollection> CreateComponentCollection()
        {
            return std::make_shared<ComponentCollection<T>>(UINT16_MAX);
        }

        // create component collection
        inline static std::shared_ptr<BaseComponentCollection> CreateComponentCollection(UniqueString componentName) 
        {
            return GetSingleton()->m_Components[componentName].CreateComponentCollection();
        };

        // serialize
        template<typename T>
        static Json Serialize(const Component* data)
        {
            T t = *((T*) data);
            return Serializer<T>::Serialize(t);
        }

        // serialize by name
        static inline Json Serialize(UniqueString componentName, const Component* data)
        {
            return GetSingleton()->m_Components[componentName].Serialize(data);
        }

        // deserialize
        template <typename T>
        static void Deserialize(const Json &object, Component* dest)
        {
            T t;
            Serializer<T>::Deserialize(object, t);
            CopyComponent<T>(dest, (Component*) &t);
        }

        // deserialize
        static inline void Deserialize(UniqueString componentName, const Json& object, Component* dest)
        {
            return GetSingleton()->m_Components[componentName].Deserialize(object, dest);
        }

        // make component
        template <typename T>
        static Component *MakeComponent(const Component* value)
        {
            // check if component is of component type
            static_assert(std::is_base_of_v<TComponent<T>, T>);
            T* newComponent = new T();

            if (value != nullptr)
            {
                *newComponent = *((T*) value);
            }

            return (Component*) newComponent;
        }

        // make component by name
        static inline Component *MakeComponent(UniqueString componentName, const Component *value)
        {
            return GetSingleton()->m_Components[componentName].MakeComponent(value);
        }

        // destroy component
        template <typename T>
        static void DeleteComponent(Component *value)
        {
            // check if component is of component type
            static_assert(std::is_base_of_v<TComponent<T>, T>);
            T* castedComponent = (T*) value;
            delete castedComponent;
        }

        // destroy component by name
        static inline void DeleteComponent(UniqueString componentName, Component *value)
        {
            GetSingleton()->m_Components[componentName].DeleteComponent(value);
        }

        // copy component from one to another
        template <typename T>
        static void CopyComponent(Component* dest, const Component* src)
        {
            static_assert(std::is_base_of_v<TComponent<T>, T>);
            T* castedDest = (T*) dest;
            const T* castedSrc = (T*) src;

            *castedDest = *castedSrc;
        }

        // copy component from one to another base on name
        inline static void CopyComponent(UniqueString componentName, Component *dest, const Component *src)
        {
            GetSingleton()->m_Components[componentName].CopyComponent(dest, src);
        }

        // get size of a component
        inline static size_t GetSize(UniqueString componentName) { return GetSingleton()->m_Components[componentName].Size; }

        // get signature
        template<typename T, typename... types>
        static void GetSignature(Signature& signature)
        {
            static_assert(std::is_base_of_v<TComponent<T>, T>);
            signature.emplace(T::s_Name);

            if constexpr (sizeof...(types) > 0)
            {
                GetSignature<types...>(signature);
            }
        }

    private:
        template <typename T>
        void IRegisterComponent(UniqueString componentName);

        // component infos
        std::unordered_map<UniqueString, ComponentInfo> m_Components;

    };

    // implementations

    // register component implementation
    template <typename T>
    void ComponentManager::IRegisterComponent(UniqueString componentName)
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<TComponent<T>, T>);

        // register component
        TComponent<T>::s_Name = componentName;

        // add component info
        ComponentInfo info;
        info.Name = componentName;
        info.Size = sizeof(T);
        info.CreateComponentCollection = ComponentManager::CreateComponentCollection<T>;
        info.Deserialize = ComponentManager::Deserialize<T>;
        info.Serialize = ComponentManager::Serialize<T>;
        info.MakeComponent = ComponentManager::MakeComponent<T>;
        info.DeleteComponent = ComponentManager::DeleteComponent<T>;
        info.CopyComponent = ComponentManager::CopyComponent<T>;

        m_Components[componentName] = info;

    };


} // namespace ASEngine


#endif