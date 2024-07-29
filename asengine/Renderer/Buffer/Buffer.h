#ifndef __ASENGINE_BUFFER_H
#define __ASENGINE_BUFFER_H

#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"

#include "Core/Memory/ByteBuffer.h"



namespace ASEngine
{
    // buffer type
    enum class BufferType
    {
        NONE = 0,
        INDEX,
        ARRAY,
        UNIFORM_BUFFER
    };

    // abstract class for rendering buffer
    class  Buffer : public Resource
    {
    ASENGINE_DEFINE_RESOURCE(Buffer);
    public:
        virtual ~Buffer() {};

        // create buffer
        void Create(BufferType type);

        // set data of buffer
        inline void SetData(const ByteBuffer &data)
        {
            SetData(data.GetData(), data.GetSize());
        }

        // set data of buffer
        void SetData(const void* data, size_t size);

        // get data size
        inline size_t GetSize() const
        {
            return m_Size;
        }

        // get buffer type
        inline BufferType GetType() const
        {
            return m_Type;
        }

    protected:
        // implementation of buffer creation
        virtual void CreateImp(BufferType type) = 0;

        // implementation of buffer set data
        virtual void SetDataImp(const void *data, size_t size) = 0;

    private:
        BufferType m_Type = BufferType::NONE;
        size_t m_Size = 0;
    };
} // namespace ASEngine


#endif // __ASENGINE_BUFFER_H