#include "ComponentManager.h"

namespace ASEngine
{
    uint32_t ComponentManager::GetSignature(TDynamicArray<UniqueString> &componentNames)
    {
        uint32_t signature = 1;
        for (auto& componentName: componentNames)
        {
            signature *= GetSignature(componentName);
        }
        return signature;
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
