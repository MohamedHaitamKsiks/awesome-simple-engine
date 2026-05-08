#include "Quaternion.h"
#include "Math.h"

namespace ASEngine
{
    float Quaternion::Norm() const
    {
        float normSquared = NormSquared();
        return Math::Sqrt(normSquared);
    }

} // namespace ASEngine
