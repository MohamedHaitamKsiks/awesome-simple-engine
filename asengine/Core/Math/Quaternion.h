#ifndef __ASENGINE_QUATERNION_H
#define __ASENGINE_QUATERNION_H

#include "API/API.h"

namespace ASEngine
{
    // defintion of quaternion used for 3d rotations
    struct ASENGINE_API Quaternion
    {
        // quaternion axies
        // real part
        float x;
        // vector part
        float y;
        float z;
        float w;

        // define operaions
        // todo...
        
    };
} // namespace ASEngine


#endif // __ASENGINE_QUATERNION_H