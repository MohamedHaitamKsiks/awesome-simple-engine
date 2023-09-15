#include "registry.h"

void ECSRegistry()
{
	ComponentManager::RegisterComponent<SpriteRenderer2D>(UniqueString("SpriteRenderer2D"));
	ComponentManager::RegisterComponent<RectangleRenderer2D>(UniqueString("RectangleRenderer2D"));
	ComponentManager::RegisterComponent<AudioPlayer2D>(UniqueString("AudioPlayer2D"));
	ComponentManager::RegisterComponent<Transform2D>(UniqueString("Transform2D"));
	SystemManager::RegisterSystem<SpriteRenderingSystem2D>();
	SystemManager::RegisterSystem<RectangleRenderingSystem2D>();
}