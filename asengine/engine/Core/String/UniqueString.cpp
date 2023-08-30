#include "UniqueString.h"

namespace ASEngine
{
    UniqueString::UniqueString(const std::string &str)
    {
        m_Id = UniqueStringManager::GetSingleton()->Create(str);
    }

    UniqueString::UniqueString(UniqueStringID id)
    {
        m_Id = id;
    }


} // namespace ASEngine
