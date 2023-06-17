#include "UniqueString.h"

namespace ASEngine
{
    UniqueString::UniqueString(const std::string &str)
    {
        id = UniqueStringManager::getSingleton()->create(str);
    }

    UniqueString::UniqueString(UniqueStringID _id)
    {
        id = _id;
    }

    bool UniqueString::operator==(const UniqueString &uStr)
    {
        return id == uStr.id;
    }

    size_t UniqueString::getLength() const
    {
        return UniqueStringManager::getSingleton()->getLength(id);
    }

    UniqueStringID UniqueString::getId() const
    {
        return id;
    }

    std::string UniqueString::getString() const
    {
        return UniqueStringManager::getSingleton()->getString(id);
    }

} // namespace ASEngine
