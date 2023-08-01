
#ifndef ASENGINE_SCENE_H
#define ASENGINE_SCENE_H

#include "Resource.h"
#include "ResourceManager.h"

#include "engine/FileSystem/File.h"
#include "engine/Log/Log.h"

namespace ASEngine {

	class Scene: public Resource
	{
	public:
		//load scene from file
		bool Load(const std::string& sceneFilePath);

		static void ImportAll();
	};

} // ASEngine

#endif // ASENGINE_SCENE_H
