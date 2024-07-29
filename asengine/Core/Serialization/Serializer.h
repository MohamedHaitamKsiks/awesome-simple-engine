#ifndef __ASENGINE_SERIALIZER_H
#define __ASENGINE_SERIALIZER_H



#include<string>
#include "Core/Error/Assertion.h"
#include "Json.h"

namespace ASEngine
{
    // serializer of a type
    class  Serializer
    {
    public:
        // serialize
        template <typename T>
        static Json Serialize(const T &value);

        // deserialize
        template <typename T>
        static void Deserialize(const Json &object, T &dest);

        // serialize vectors of serializable classes
        template <typename T>
        static Json Serialize(const std::vector<T> &value)
        {
            Json array;
            for(auto& item: value)
            {
                array.push_back(Serialize(item));
            }

            return array;
        }

        template <typename T>
        static void Deserialize(const Json &object, std::vector<T> &dest)
        {
            ASENGINE_ASSERT(object.is_array(), "Can't deserialize std::string if Json object is not a string");
            dest.clear();

            for (auto& item: object)
            {
                T& deserializedItem = dest.emplace_back();
                Deserialize(item, deserializedItem);
            }
        }
    };
    

} // namespace ASEngine


#endif // __ASENGINE_SERIALIZER_H