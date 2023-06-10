
#include "File.h"

/*
    Desktop implementation for files
*/

namespace ASEngine
{

    bool File::open(const std::string &_path, FileOpenMode _mode)
    {
        file.open("assets/" + _path, std::ios::binary | std::ios::in);
        //check if file is loaded
        if(!file) {
            Log::out("Error loading " + _path + "!");
            return false;
        }

        //get file size
        file.seekg(0, std::ios::end);
        size = (size_t) file.tellg();
        return true;
    }

    void File::close()
    {
        file.close();
    }

    void File::read(char *buffer)
    {
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
    }

    void File::write(const char *buffer, const size_t length)
    {
        /*todo later*/
    }

    std::string File::readText()
    {
        std::string line;
        std::stringstream textStringStream;

        while (std::getline(file, line))
        {
            textStringStream << line << "\n";
        }

        return textStringStream.str();
    }

} // ASEngine