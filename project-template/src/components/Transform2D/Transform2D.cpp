#include "Transform2D.h"

EXPORT(Transform2D, Position, Scale, Rotation)

void Transform2D::OnCreate()
{
    Rotation *= M_PI / 180.0f;
}