#include "mat4.h"

namespace ASEngine
{
    std::string mat4::ToString()
    {
        std::ostringstream ss;

        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 4; i++)
                ss << (*this)[j][i] << ",";
            
        }
        return ss.str();
    }
} // namespace ASEngine
