//
// Created by ksiks_wa3r on 3/13/23.
//

#ifndef MY_APPLICATION_RESOURCE_H
#define MY_APPLICATION_RESOURCE_H

#include <unordered_map>
#include <string>
#include <sstream>

#include <android/asset_manager.h>
#include "../Log/Log.h"

namespace ASEngine {

    typedef std::string ResourceID;

    class Resource {
    public:
#ifdef __ANDROID__
        //use assets manager for android devices
        static void init(AAssetManager* _assetManager);
        static AAssetManager* assetManager;
#endif

        static std::string loadAsText(const std::string& filePath);
        static char* loadAsBinary(const std::string& filePath, size_t* fileLength);
        static ResourceID generateId();
        static void terminate();

        //resource object
        ResourceID id = "";
        Resource() {};
        virtual void destroy() = 0;

    private:
        static uint32_t resourceCounter;

    };

} // ASEngine

#endif //MY_APPLICATION_RESOURCE_H
