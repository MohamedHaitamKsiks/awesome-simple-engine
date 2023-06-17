
#include "File.h"

/*
    Android implementation for files
*/

namespace ASEngine
{

    AAssetManager* File::assetManager = nullptr;

    void File::setAssetManager(AAssetManager *_assetManager) 
    {
        assetManager = _assetManager;
    }

    AAssetManager* File::getAssetManager()
    {
        return assetManager;
    }

    bool File::open(const std::string &_path, FileOpenMode _mode)
    {
        asset = AAssetManager_open(assetManager, _path.c_str(), AASSET_MODE_BUFFER);
        size = (size_t) AAsset_getLength(asset);
        return asset != nullptr;
    }

    void File::close()
    {
        AAsset_close(asset);
    }

    void File::read(char *buffer)
    {
        AAsset_read(asset, buffer, size);
    }

    void File::write(const char *buffer, const size_t length)
    {

    }

    std::string File::readText()
    {
        //create buffer
        char buffer[size];
            
        //read char by char
        char readChar;
        uint32_t currentChar = 0;
        while (currentChar < size)
        {
            AAsset_read(asset, &readChar, sizeof(char));
            if (readChar == EOF)
            {
                break;
            }
            buffer[currentChar] = readChar;
            currentChar++;
        };

        std::string text(buffer, buffer + currentChar);

        return text;
    }

} // ASEngine