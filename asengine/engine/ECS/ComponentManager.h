#ifndef ASENGINE_COMPONENT_MANAGER_H
#define ASENGINE_COMPONENT_MANAGER_H

#include <memory>
#include <cstdint>
#include <type_traits>
#include <unordered_map>

#include "Core/Serialization/Serializer.h"
#include "Core/Singleton/Singleton.h"

#include "Component.h"


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
        uint32_t Signature;
        size_t Size = 0;
        std::shared_ptr<BaseComponentCollection> (*CreateComponentCollection)();
        Json (*Serialize)(const Component*);
        void (*Deserialize)(const Json&, Component*);
        Component* (*MakeComponent)(const Component*);
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
            memcpy(dest, &t, sizeof(T));
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
            T* newComponent = new T;

            if (value != nullptr)
                *newComponent = *((T*) value);

            return (Component*) newComponent;
        }

        // make component by name
        static inline Component *MakeComponent(UniqueString componentName, const Component *value)
        {
            return GetSingleton()->m_Components[componentName].MakeComponent(value);
        }

        // copy component from one to another
        template <typename T>
        static void CopyComponent(Component* dest, const Component* src)
        {
            static_assert(std::is_base_of_v<TComponent<T>, T>);
            T* castedDest = (T*) dest;
            *castedDest = *((T*) src);
        }

        // copy component from one to another base on name
        inline static void CopyComponent(UniqueString componentName, Component *dest, const Component *src)
        {
            GetSingleton()->m_Components[componentName].CopyComponent(dest, src);
        }

        // get signature of a composition of components
        template <typename T, typename... types>
        static uint32_t GetSignature();

        // get signature of a component
        inline static uint32_t GetSignature(UniqueString componentName) { return GetSingleton()->m_Components[componentName].Signature; }

        // get signature of a list of component names
        static uint32_t GetSignature(TDynamicArray<UniqueString>& componentNames);

        // get size of a component
        inline static size_t GetSize(UniqueString componentName) { return GetSingleton()->m_Components[componentName].Size; }

    private:
        template <typename T>
        void IRegisterComponent(UniqueString componentName);

        // is valid signature <===> is prime
        bool IsValidSignature(uint32_t signature);

        // last component signature
        uint32_t m_LastComponentSignature = 1;

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

        // create signature
        int currentNumber = m_LastComponentSignature + 1;
        for (uint32_t i = m_LastComponentSignature + 1; i < UINT32_MAX; i++)
        {
            if (IsValidSignature(i))
            {
                // register component
                TComponent<T>::s_Signature = i;
                TComponent<T>::s_Name = componentName;

                // add component info
                ComponentInfo info;
                info.Name = componentName;
                info.Signature = i;
                info.Size = sizeof(T);
                info.CreateComponentCollection = ComponentManager::CreateComponentCollection<T>;
                info.Deserialize = ComponentManager::Deserialize<T>;
                info.Serialize = ComponentManager::Serialize<T>;
                info.MakeComponent = ComponentManager::MakeComponent<T>;
                info.CopyComponent = ComponentManager::CopyComponent<T>;

                m_Components[componentName] = info;

                // update last component signature
                m_LastComponentSignature = i;
                return;
            }
        }
    };

    // get signature implementation
    template <typename T, typename... types>
    uint32_t ComponentManager::GetSignature()
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<TComponent<T>, T>);

        // compute signature
        uint32_t signature = GetSignature(TComponent<T>::s_Name);
        if constexpr (sizeof...(types) > 0)
        {
            signature *= GetSignature<types...>();
        }

        return signature;
    };

} // namespace ASEngine


#endif