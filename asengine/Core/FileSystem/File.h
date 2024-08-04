#ifndef __ASENGINE_FILESYSTEM_H
#define __ASENGINE_FILESYSTEM_H

#include <fstream>


#include<string>
#include "Core/Memory/ByteBuffer.h"


namespace ASEngine
{
    enum class FileOpenMode
    {
        NONE = 0,
        // open file in read mode
        READ,
        // open file in write mode
        WRITE
    };

    enum class FileType
    {
        NONE = 0,
        // read only assets file located in the ./assets folder
        ASSETS,
        // user data files
        USERDATA
    };

    class  File
    {
    public:
        File() = default;
        ~File();

        // open file: read | write
        // assets files starts with assets://
        // user data files starts with user://
        bool Open(const std::string &path, FileOpenMode openMode = FileOpenMode::READ);

        //get file size
        size_t GetSize();

        //read data into buffer
        void Read(void* buffer);

        // read data into bytebuffer
        void Read(ByteBuffer& buffer);

        // write data from buffer into file
        void Write(const void* buffer, size_t length);

        // write data to file
        inline void Write(const ByteBuffer& buffer)
        {
            Write(buffer.GetData(), buffer.GetSize());
        }

        //read text and return string
        std::string ReadText();

        // write text to file
        void WriteText(const std::string& text);

    private:
        struct PathInfo
        {
            std::string Path;
            FileType Type = FileType::NONE;
        };
        void ParsePath(const std::string& path, PathInfo& pathInfo);


        bool OpenWithPathInfo(const PathInfo& pathInfo, FileOpenMode openMode);

        size_t m_Size = 0;
        FileOpenMode m_Mode = FileOpenMode::READ;
        std::fstream m_File;
    };

} // ASEngine

#endif // __ASENGINE_FILESYSTEM_H
