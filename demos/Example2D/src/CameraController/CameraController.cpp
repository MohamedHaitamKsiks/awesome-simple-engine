#include "CameraController.h"

namespace ASEngine {
template class ComponentClass<CameraController>;
}
ASENGINE_SERIALIZE_STRUCT_EMPTY(CameraController);

void CameraController::OnCreate(EntityID entityID)
{
}

void CameraController::OnDestroy()
{
}
