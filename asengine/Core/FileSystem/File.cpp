#include "File.h"
#include <sstream>
#include "Core/Debug/Debug.h"

#include <memory>

namespace ASEngine {

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

    bool File::Open(const std::string &path, FileOpenMode mode, FileType type)
    {
        m_File.open("assets/" + path, std::ios::binary | std::ios::in);
        // check if file is loaded
        if (!m_File)
        {
            Debug::Error("Error loading", path, "!");
            return false;
        }

        // get file size
        m_File.seekg(0, std::ios::end);
        m_Size = (size_t)m_File.tellg();
        return true;
    }

    void File::Close()
    {
        m_File.close();
    }

    void File::Write(const void *buffer, size_t length)
    {
        /*todo later*/
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

} // ASEngine