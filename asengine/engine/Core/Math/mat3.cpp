#include "mat3.h"

namespace ASEngine
{
    std::string mat3::ToString()
    {
        std::ostringstream ss;

        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 3; i++)
                ss << (*this)[i][j] << ",";
        }
        
        return ss.str();
    }
} // namespace ASEngine
