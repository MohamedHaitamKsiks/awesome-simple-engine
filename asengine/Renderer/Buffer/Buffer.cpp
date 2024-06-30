#include "Buffer.h"

#include "Resource/ResourceRefSerialization.h"

#include "Core/Error/Assertion.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

ASENGINE_SERIALIZE_RESOURCE_REF(Buffer);

namespace ASEngine
{
    void Buffer::Create(BufferType type)
    {
        ASENGINE_ASSERT(type != BufferType::NONE, "BufferType shouldn't be NONE!");
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
