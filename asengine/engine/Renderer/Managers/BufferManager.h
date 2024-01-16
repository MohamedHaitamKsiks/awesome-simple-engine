#ifndef ASENGINE_BUFFER_H
#define ASENGINE_BUFFER_H

#include "Core/Error/Exception.h"
#include "Core/Memory/PoolAllocator.h"

#include "Renderer/GraphicsAPI.h"

namespace ASEngine
{
    // buffer type
    enum class BufferType
    {
        INDEX,
        ARRAY,
        // number of buffer types
        COUNT
    };

    DEFINE_EXCEPTION(BufferInvalidTypeException, "Invalid Buffer Type!");
    DEFINE_EXCEPTION(BufferOutOfRangeException, "Buffer Out of range!");

    // contains general buffer informations + api specific informations
    struct BufferInfo
    {
    #ifdef OPENGL
        GLuint GLBufferID;
        GLuint GLBufferType;
    #endif //OPENGL
        BufferType Type;
        size_t Size = 0;
    };

    using BufferID = ChunkID;

    // manages gpu buffers 
    class BufferManager
    {
    public:
        BufferManager();
        ~BufferManager() {};

        BufferID Create(BufferType bufferType);

        inline const BufferInfo& GetBufferInfo(BufferID bufferID) const
        {
            return m_BufferInfos.Get(bufferID);
        }

        void Allocate(BufferID bufferID, size_t size, const void* data = nullptr);
        
        void SetData(BufferID bufferID, size_t offset, size_t size, const void* data);

        void Delete(BufferID bufferID);

    private:
        TPoolAllocator<BufferInfo> m_BufferInfos{2};
    };
} // namespace ASEngine


#endif // ASENGINE_BUFFER_H