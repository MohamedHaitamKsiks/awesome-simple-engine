#ifndef ASENGINE_TRANSFORM_COMPONENT_H
#define ASENGINE_TRANSFORM_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds transoorm data
class TransformComponent: public Component<TransformComponent>
{
public:
    vec2 position;
};



#endif