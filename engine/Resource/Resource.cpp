//
// Created by ksiks_wa3r on 3/13/23.
//

#include "Resource.h"

namespace ASEngine {

    ResourceID Resource::generateId() {
        std::ostringstream os;
        os << resourceCounter++;
        ResourceID resourceId = os.str();
        return resourceId;
    }

    void Resource::terminate() {
        resourceCounter = 0;
    }

    uint32_t Resource::resourceCounter = 0;


#ifdef __ANDROID__
    AAssetManager* Resource::assetManager = nullptr;
    void Resource::init(AAssetManager *_assetManager) {
        assetManager = _assetManager;
    }

    std::string Resource::loadAsText(const std::string& filePath) {
        //open asset
        AAsset* asset = AAssetManager_open(assetManager, filePath.c_str(), AASSET_MODE_BUFFER);

        // Get the length of the file using AAsset_getLength.
        off_t fileLength = AAsset_getLength(asset);

        // Read the contents of the file using AAsset_read.
        char* buffer = new char[fileLength];
        char readChar;
        uint32_t currentChar = 0;
        while (currentChar < fileLength) {
            AAsset_read(asset, &readChar, sizeof(char));
            //end of file
            if (readChar == EOF) {
                break;
            }
            //add char
            buffer[currentChar] = readChar;
            currentChar++;
        };

        std::string text(buffer, buffer + currentChar);

        //free buffer
        AAsset_close(asset);
        free(buffer);
        return text;
    }

    char* Resource::loadAsBinary(const std::string& filePath, size_t* fileLength) {
        //open asset
        AAsset* asset = AAssetManager_open(assetManager, filePath.c_str(), AASSET_MODE_BUFFER);

        // Get the length of the file using AAsset_getLength.
        *fileLength = (size_t) AAsset_getLength(asset);

        // Read the contents of the file using AAsset_read.
        char* buffer = new char[*fileLength];
        int bytesRead = AAsset_read(asset, buffer, *fileLength);

        AAsset_close(asset);

        return  buffer;

    }

#endif

} // ASEngine