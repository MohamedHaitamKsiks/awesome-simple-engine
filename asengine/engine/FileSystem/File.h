#ifndef ASENGINE_FILESYSTEM_H
#define ASENGINE_FILESYSTEM_H


#ifdef __ANDROID__
#include <android/asset_manager.h>

#else
#include <fstream>

#endif

#include<string>
#include<sstream>

#include "engine/Log/Log.h"

namespace ASEngine {

    enum FileOpenMode
    {
        // do not open files with this mode, this is the default mode
        FILE_OPEN_MODE_NONE,
        // open file in read mode
        FILE_OPEN_MODE_READ,
        // open file in write mode
        FILE_OPEN_MODE_WRITE,
    };

    enum FileType { 
        //file is a resource, resource files are readonly files
        FILE_TYPE_RESOURCE,
        //file is used to store game data like saves, settings ...
        FILE_TYPE_USERDATA
    };

    class File {
    
    public:
        //get/set assetmanager for android 
        #ifdef __ANDROID__
        static void setAssetManager(AAssetManager *_assetManager);
        static AAssetManager* getAssetManager();
        #endif

        // open file: read | write
        bool open(const std::string &_path, FileOpenMode _mode);

        //close file
        void close();

        //get file size
        size_t getSize();

        //read data into buffer
        void read(char* buffer);

        //write data from buffer into file
        void write(const char* buffer, const size_t length);

        //read text and return string
        std::string readText();



    private:
        size_t size = -1;
        FileOpenMode mode = FILE_OPEN_MODE_NONE;
        
        #ifdef  __ANDROID__
        static AAssetManager* assetManager;
        AAsset* asset = nullptr;

        #else
        std::fstream file;

        #endif
    };

} // ASEngine

#endif // ASENGINE_FILESYSTEM_H
