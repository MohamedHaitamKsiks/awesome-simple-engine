#include "File.h"
#include <sstream>
#include "Core/Debug/Debug.h"

#include <memory>

namespace ASEngine {

    size_t File::GetSize()
    {
        return m_Size;
    }

    void File::Read(ByteBuffer &buffer)
    {
        std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(m_Size);
        buffer.SetData(data.get(), m_Size);
    }

} // ASEngine