#include "CameraControllerSystem.h"

#include "CameraController.h"

#define MAX_MOVEMENT_SPEED 100.0f

void CameraControllerSystem::Update(float delta)
{
    EntityQuery<CameraController, Transform2D> query{};
    query.ForEach([delta](CameraController& cameraController, Transform2D& transform2D)
    {
        Vector2 direction = Vector2::ZERO();
        
        direction.x = static_cast<float>(cameraController.IsRightPressed) - static_cast<float>(cameraController.IsLeftPressed);
        direction.y = static_cast<float>(cameraController.IsDownPressed) - static_cast<float>(cameraController.IsUpPressed);
    
        if (direction.Length() > 0.01f)
            direction = direction.Normalize();
    
        transform2D.Position += direction * MAX_MOVEMENT_SPEED * delta;
    });
}

void CameraControllerSystem::OnInputEvent(const InputEvent &event)
{
    if (event.GetType() != InputEventType::KEYBOARD)
        return;

    const InputEventKeyboard& keyEvent = event.Get<InputEventKeyboard>(); 

    EntityQuery<CameraController> query{};
    query.ForEach([&keyEvent](CameraController& cameraController)
    {
        if (keyEvent.Code == Keycode::KEY_W)
            cameraController.IsUpPressed = keyEvent.Pressed;
        else if (keyEvent.Code == Keycode::KEY_A)
            cameraController.IsLeftPressed = keyEvent.Pressed;
        else if (keyEvent.Code == Keycode::KEY_D)
            cameraController.IsRightPressed = keyEvent.Pressed;
        else if (keyEvent.Code == Keycode::KEY_S)
            cameraController.IsDownPressed = keyEvent.Pressed;
    });
}
