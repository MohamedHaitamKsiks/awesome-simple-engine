
#include "File.h"

/*
    Desktop implementation for files
*/

namespace ASEngine
{

    bool File::Open(const std::string &path, FileOpenMode mode)
    {
        m_File.open("assets/" + path, std::ios::binary | std::ios::in);
        //check if file is loaded
        if(!m_File) {
            Debug::Log("Error loading", path, "!");
            return false;
        }

        //get file size
        m_File.seekg(0, std::ios::end);
        m_Size = (size_t) m_File.tellg();
        return true;
    }

    void File::Close()
    {
        m_File.close();
    }

    void File::Read(char *buffer)
    {
        m_File.seekg(0, std::ios::beg);
        m_File.read(buffer, m_Size);
    }

    void File::Write(const char *buffer, const size_t length)
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