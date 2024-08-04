#include "File.h"
#include "Core/Debug/Debug.h"
#include "Core/Error/Assertion.h"

#include <sstream>

namespace ASEngine
{
    File::~File()
    {
        if (m_File)
            m_File.close();
    }

    size_t File::GetSize()
    {
        return m_Size;
    }

    void File::Read(ByteBuffer &buffer)
    {
        buffer.SetData(nullptr, m_Size);
        Read(buffer.GetData());
    }

    void File::Read(void *buffer)
    {
        m_File.seekg(0, std::ios::beg);
        m_File.read(reinterpret_cast<char *>(buffer), m_Size);
    }

    void File::ParsePath(const std::string& path, PathInfo& pathInfo)
    {
        pathInfo.Type = FileType::NONE;

        const std::string assetsPath = "assets://";
        const std::string userdataPath = "user://";

        if (path.find(assetsPath) == 0)
        {
            pathInfo.Path = path.substr(assetsPath.size());
            pathInfo.Type = FileType::ASSETS;
        }
        else if (path.find(userdataPath) == 0)
        {
            pathInfo.Path = path.substr(userdataPath.size());
            pathInfo.Type = FileType::USERDATA;
        }
        else
        {
            Debug::Error("Invalid path: ", path);
        }
    }

    bool File::OpenWithPathInfo(const PathInfo& pathInfo, FileOpenMode openMode)
    {
        ASENGINE_ASSERT(pathInfo.Type != FileType::NONE, "Invalid file type");
        ASENGINE_ASSERT(!(openMode == FileOpenMode::WRITE && pathInfo.Type == FileType::ASSETS), "Cannot write in assets file");

        std::stringstream ssPath;
        if (pathInfo.Type == FileType::ASSETS)
            ssPath << "assets/";
        else if (pathInfo.Type == FileType::USERDATA)
            ssPath << "userdata/";

        ssPath << pathInfo.Path;

        m_File.open(ssPath.str(), std::ios::binary | std::ios::in);

        // check if file is loaded
        if (!m_File)
            return false;

        m_File.seekg(0, std::ios::end);
        m_Size = (size_t)m_File.tellg();

        return true;
    }

    bool File::Open(const std::string &path, FileOpenMode openMode)
    {
        PathInfo pathInfo{};
        ParsePath(path, pathInfo);

        bool isOpened = OpenWithPathInfo(pathInfo, openMode);
        if (!isOpened)
        {
            Debug::Error("Coudn't load ", path);
        }

        return isOpened;
    }

    void File::Write(const void *buffer, size_t length)
    {
        m_File.write(static_cast<const char*>(buffer), length);
    }

    std::string File::ReadText()
    {
        std::string line;
        std::stringstream textStringStream;
        m_File.seekg(0, std::ios::beg);

        while (std::getline(m_File, line))
        {
            textStringStream << line << "\n";
        }

        return textStringStream.str();
    }

    void File::WriteText(const std::string& text)
    {
        Write(text.c_str(), text.capacity());
    }
} // ASEngine
