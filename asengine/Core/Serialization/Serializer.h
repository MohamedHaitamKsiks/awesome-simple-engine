#ifndef __ASENGINE_SERIALIZER_H
#define __ASENGINE_SERIALIZER_H

#include<string>
#include "Core/Error/Assertion.h"
#include "Json.h"

namespace ASEngine
{
    // serializer of a type
    template <typename T>
    class Serializer
    {
    public:
        // serialize
        static Json Serialize(const T& value);

        // deserialize
        static void Deserialize(const Json& object, T& dest);
    
        // serialize vectors of serializable classes
        static Json Serialize(const std::vector<T>& value)
        {
            Json array;
            for(auto& item: value)
            {
                array.push_back(Serialize<T>(item));
            }

            return array;
        }
        void Deserialize(const Json &object, std::vector<T> &dest)
        {
            ASENGINE_ASSERT(object.is_array(), "Can't deserialize std::string if Json object is not a string");
            dest.clear();

            for (auto& item: object)
            {
                T deserializedItem;
                Deserialize<T>(item, deserializedItem);
                dest.push_back(deserializedItem);
            }
        }
    };
    

} // namespace ASEngine


#endif // __ASENGINE_SERIALIZER_H