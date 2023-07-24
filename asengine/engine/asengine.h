
#ifndef ASENGINE_H
#define ASENGINE_H


//log
#include "Log/Log.h"

//core
#include "FileSystem/File.h"
#include "Math/mat3.h"
#include "Math/vec2.h"
#include "Math/Random.h"
#include "Memory/PoolAllocator.h"
#include "String/UniqueString.h"
#include "Signals/Signal.h"

// ecs
#include "ECS/World.h"
#include "ECS/Component.h"
#include "ECS/ComponentManager.h"
#include "ECS/Entity.h"
#include "ECS/System.h"
#include "ECS/SystemManager.h"
#include "ECS/Archetype.h"
#include "ECS/ArchetypeManager.h"

//resources
#include "Resource/ResourceManager.h"
#include "Resource/Image.h"
#include "Resource/Sprite.h"
#include "Resource/Material.h"
#include "Resource/Shader.h"
#include "Resource/Font.h"
#include "Resource/Scene.h"


//rendering
#include "Renderer/Texture.h"
#include "Renderer/2D/Renderer2D.h"
#include "Renderer/2D/Quad2D.h"
#include "Renderer/Color.h"
#include "Renderer/Viewport.h"
#include "Window/Window.h"

//input
#include "InputEvent/InputEvent.h"

//application
#include "Application/Application.h"

//interpolation
#include "Interpolation/Interpolate.h"

//shape
#include "Shape/Rectangle.h"


#endif //MY_APPLICATION_ASENGINE_H
