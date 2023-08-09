#include "ComponentManager.h"

namespace ASEngine
{

    std::shared_ptr<BaseComponentCollection> ComponentManager::ICreateComponentCollection(UniqueString componentName)
    {
        return m_Components[componentName].CreateComponentCollection();
    }

    uint32_t ComponentManager::IGetSignature(UniqueString componentName)
    {
        return m_Components[componentName].Signature;
    }

    bool ComponentManager::IsValidSignature(uint32_t signature)
    {
        for (uint32_t k = 2; k * k < signature * signature; k++)
        {
            if (signature % k == 0)
                return false;
        }
        return signature > 1;
    }

} // namespace ASEngine
