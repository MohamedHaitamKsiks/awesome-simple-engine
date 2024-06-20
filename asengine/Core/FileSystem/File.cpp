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
        buffer.SetData(nullptr, m_Size);
        Read(buffer.GetData());
    }

} // ASEngine