#include "ComponentManager.h"

namespace ASEngine
{

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
