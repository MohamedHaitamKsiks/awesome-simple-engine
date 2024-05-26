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

    void Buffer::SetData(const ByteBuffer &data)
    {
        ASENGINE_ASSERT(data.GetData(), "Data is NULL");
        SetDataImp(data);
        m_Size = data.GetSize();
    }

} // namespace ASEngine
