 #include "Viewport.h"

namespace ASEngine
{
    void Viewport::ISetSize(int width, int height)
    {
        // set size
        m_Width = width;
        m_Height = height;

        // compute projection matrix
        m_ProjectionMatrix = mat3
        {{
            2.0f / (float) m_Width, 0.0f, -1.0f,
            0.0f, -2.0f / (float) m_Height, 1.0f,
            0.0f, 0.0f, 1.0f
        }};
    }
} // namespace ASEngine
