#include "UniqueString.h"

#include "Core/Error/Assertion.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{
    UniqueString::UniqueString()
    {
        // uninsitialized string
        m_StringID = UNIQUE_STRING_ID_NULL;
    }

    UniqueString::UniqueString(const std::string &str)
    {
        Create(str);
    }

    UniqueString::UniqueString(const char *cStr)
    {
        Create(cStr);
    }

    //Serialization
    template <>
    Json Serializer<UniqueString>::Serialize(const UniqueString &value)
    {
        return Json(value.GetString());
    }
    template <>
    void Serializer<UniqueString>::Deserialize(const Json &object, UniqueString &dest)
    {
        ASENGINE_ASSERT(object.is_string(), "Can't deserialize UniqueString if Json object is not a string");
        dest = UniqueString(object);
    }

} // namespace ASEngine
