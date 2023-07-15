//
// Created by ksiks_wa3r on 4/15/23.
//

#ifndef ANDROIDSIMPLEENGINE_SCENE_H
#define ANDROIDSIMPLEENGINE_SCENE_H

#include "Resource.h"
#include "ResourceManager.h"
#include "../FileSystem/File.h"
#include "../Log/Log.h"

namespace ASEngine {

	class Scene: public Resource {
	public:
		//load scene from file
		bool load(const std::string& sceneFilePath);

		static void importAll();
	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_SCENE_H
