//
// Created by ksiks_wa3r on 4/15/23.
//

#ifndef ANDROIDSIMPLEENGINE_SCENE_H
#define ANDROIDSIMPLEENGINE_SCENE_H

#include "Resource.h"
#include "ResourceManager.h"

#include "engine/FileSystem/File.h"
#include "engine/Log/Log.h"

namespace ASEngine {

	class Scene: public Resource {
	public:
		//load scene from file
		bool Load(const std::string& sceneFilePath);

		static void ImportAll();
	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_SCENE_H
