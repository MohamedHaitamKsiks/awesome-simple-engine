//
// Created by ksiks_wa3r on 3/13/23.
//

#ifndef MY_APPLICATION_RESOURCE_H
#define MY_APPLICATION_RESOURCE_H

#include <unordered_map>
#include <string>

#include "Material.h"

namespace ASEngine {

    typedef std::string ResourceID;

    class Resource {
    public:
        //data
        std::string name;
        //init ressource manager manager
        static void init(AAssetManager* _assetManager);

        //destroy
        virtual void destroy();


        //materials
        //static std::unordered_map<std::string, Material> materials;
        //load material
        //static void loadMaterial(std::string& name, std::string& vertexFile, std::string& fragmentFile);
        //load materials from import.materials.json file
        //static void loadMaterials();

    private:
        //asset manager
        static AAssetManager* assetManager;

    };

} // ASEngine

#endif //MY_APPLICATION_RESOURCE_H
