#include "Buffer.h"

#include "Resource/ResourceRefSerialization.h"

#include "Core/Error/Assertion.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{
    ASENGINE_SERIALIZE_RESOURCE_REF(Buffer);

    // don't allow buffer to be serialized / deserialized
    template <>
    void Serializer<Buffer>::Deserialize(const Json &object, Buffer &dest)
    {
        ASENGINE_ASSERT(true, "CANNOT DESERIALIZE BUFFER!");
    }

    template <>
    Json Serializer<Buffer>::Serialize(const Buffer &value)
    {
        ASENGINE_ASSERT(true, "CANNOT SERIALIZE BUFFER!");
        return Json({});
    }

    void Buffer::Create(BufferType type)
    {
        ASENGINE_ASSERT(type != BufferType::NONE, "Buffer Type shouldn't be NONE!");
        CreateImp(type);
        m_Type = type;
    }

    void Buffer::SetData(const void *data, size_t size)
    {
        ASENGINE_ASSERT(data, "Data is NULL");
        SetDataImp(data, size);
        m_Size = size;
    }

} // namespace ASEngine
