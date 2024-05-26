#ifndef __ASENGINE_FILESYSTEM_H
#define __ASENGINE_FILESYSTEM_H


#ifdef __ANDROID__
#include <android/asset_manager.h>

#else
#include <fstream>

#endif

#include<string>
#include "Core/Memory/ByteBuffer.h"

namespace ASEngine {

    enum class FileOpenMode
    {
        // open file in read mode
        READ,
        // open file in write mode
        WRITE
    };

    enum class FileType { 
        //file is a resource, resource files are readonly files
        RESOURCE,
        //file is used to store game data like saves, settings ...
        USERDATA
    };

    class File {
    
    public:
        //get/set assetmanager for android 
        #ifdef __ANDROID__
        static void SetAssetManager(AAssetManager *assetManager);
        static inline AAssetManager* GetAssetManager() { return s_AssetManager; };
        #endif

        // open file: read | write
        bool Open(const std::string &path, FileOpenMode mode, FileType type = FileType::RESOURCE);

        //close file
        void Close();

        //get file size
        size_t GetSize();

        //read data into buffer
        void Read(void* buffer);

        // read data and return byte buffer
        void Read(ByteBuffer& buffer);

        //write data from buffer into file
        void Write(const void* buffer, size_t length);

        //read text and return string
        std::string ReadText();

    private:
        size_t m_Size = 0;
        FileOpenMode m_Mode = FileOpenMode::READ;
        
        #ifdef  __ANDROID__
        static AAssetManager* s_AssetManager;
        AAsset* m_Asset = nullptr;

        #else
        std::fstream m_File;

        #endif
    };

} // ASEngine

#endif // __ASENGINE_FILESYSTEM_H
