#ifndef __ASENGINE_BYTE_BUFFER_H
#define __ASENGINE_BYTE_BUFFER_H

#include <cstdint>
#include <cstddef>



namespace ASEngine
{
    // memory safe byte buffer to fill with data
    class  ByteBuffer
    {
    public: 
        ByteBuffer() {};
    
        // create buffer with size n
        ByteBuffer(size_t size);

        // create buffer with size and data
        ByteBuffer(const void *data, size_t size);

        // copy byte buffer
        ByteBuffer(const ByteBuffer& buffer);

        ByteBuffer& operator=(const ByteBuffer& buffer);

        // move byte buffer
        ByteBuffer(ByteBuffer&& buffer);

        ByteBuffer& operator=(ByteBuffer&& buffer);

        // cleanup
        ~ByteBuffer();


        // set buffer data (can change size of the pointer)
        inline void SetData(const void *data, size_t size)
        {
            SetDataAt(data, size, 0);
        }

        // set buffer data at
        void SetDataAt(const void* data, size_t size, size_t offset);

        // get buffer pointer
        inline const void* GetData() const
        {
            return m_Data;
        }

        inline void *GetData()
        {
            return m_Data;
        }

        // get buffer size
        inline size_t GetSize() const
        {
            return m_Size;
        }

        //  move data ownershipt to this
        void Move(void* data, size_t size);

    private:
        void* m_Data = nullptr;
        size_t m_Size = 0;
        // copy byte buffer and erase current one
        void Copy(const ByteBuffer& buffer);
    
        // move byte buffer
        void Move(ByteBuffer& buffer);
    };
} // namespace ASEngine


#endif // __ASENGINE_BYTE_BUFFER_H