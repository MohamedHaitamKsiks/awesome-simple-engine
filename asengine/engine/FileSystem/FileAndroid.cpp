#include "File.h"
#include "android/asset_manager.h"

/*
    Android implementation for files
*/

namespace ASEngine
{

    AAssetManager* File::s_AssetManager = nullptr;

    void File::SetAssetManager(AAssetManager *assetManager) 
    {
        s_AssetManager = assetManager;
    }

    bool File::Open(const std::string &path, FileOpenMode mode)
    {
        m_Asset = AAssetManager_open(s_AssetManager, path.c_str(), AASSET_MODE_BUFFER);
        m_Size = (size_t) AAsset_getLength(m_Asset);
        return m_Asset != nullptr;
    }

    void File::Close()
    {
        AAsset_close(m_Asset);
    }

    void File::Read(char *buffer)
    {
        AAsset_read(m_Asset, buffer, m_Size);
    }

    void File::Write(const char *buffer, const size_t length)
    {

    }

    std::string File::ReadText()
    {
        //create buffer
        char buffer[m_Size];
            
        //read char by char
        char readChar;
        uint32_t currentChar = 0;
        while (currentChar < m_Size)
        {
            AAsset_read(m_Asset, &readChar, sizeof(char));
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