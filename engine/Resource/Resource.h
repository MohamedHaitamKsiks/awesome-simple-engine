//
// Created by ksiks_wa3r on 3/13/23.
//

#ifndef MY_APPLICATION_RESOURCE_H
#define MY_APPLICATION_RESOURCE_H

#include <unordered_map>
#include <string>
#include <sstream>

#include "../log.h"
#include <android/asset_manager.h>

namespace ASEngine {

    typedef std::string ResourceID;

    class Resource {
    public:
        //asset manager
        static AAssetManager* assetManager;
        //data
        ResourceID id = "";
        //default constructos
        Resource() {};

        //init resource manager manager
        static void init(AAssetManager* _assetManager);

        //load file as text
        static std::string loadAsText(const std::string& filePath);

        //destroy
        virtual void destroy();

        //static generate id
        static ResourceID generateId();

        //terminate all
        static void terminate();

    private:
        static uint32_t resourceCounter;

    };

} // ASEngine

#endif //MY_APPLICATION_RESOURCE_H
