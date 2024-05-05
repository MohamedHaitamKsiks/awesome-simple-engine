 #include "Viewport.h"

namespace ASEngine
{
    void Viewport::SetSize(int width, int height)
    {
        // set size
        m_Width = width;
        m_Height = height;

        // compute projection matrix
        m_ProjectionMatrix = Matrix3x3{{
            2.0f / (float) m_Width, 0.0f,                     0.0f, 0.0f,
            0.0f,                   -2.0f / (float) m_Height, 0.0f, 0.0f,
            -1.0f,                  1.0f,                     1.0f, 0.0f
        }};
    }
} // namespace ASEngine
