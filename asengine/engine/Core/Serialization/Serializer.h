#ifndef ASENGINE_SERIALIZABLE_H
#define ASENGINE_SERIALIZABLE_H

#include<string>
#include <cassert>


#include "Thirdparty/json.hpp"

namespace ASEngine
{
    // json object
    using Json = nlohmann::json;

    // serializer of a type
    template <typename T>
    class Serializer
    {
    public:
        // serialize
        static Json Serialize(const T& value);

        // deserialize
        static void Deserialize(const Json& object, T& dest);
    };



} // namespace ASEngine


#endif // ASENGINE_SERIALIZABLE_H