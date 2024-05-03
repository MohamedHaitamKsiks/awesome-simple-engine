#ifndef ASENGINE_VIEWPORT_H
#define ASENGINE_VIEWPORT_H

#include "Core/Singleton/Singleton.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Matrix3x3.h"

namespace ASEngine
{
    class Viewport: public Singleton<Viewport>
    {
    public:
        // set view port size
        void SetSize(int width, int height);

        // get projection matrix
        inline Matrix3x3 GetProjectionMatrix() 
        { 
            return m_ProjectionMatrix; 
        }

        // get size
        inline Vector2 GetSize()
        {
            return Vector2{
                static_cast<float>(m_Width), 
                static_cast<float>(m_Height)
            };
        };
    private:
        // view port size
        int m_Width = -1;
        int m_Height = -1;

        // projection matrix
        Matrix3x3 m_ProjectionMatrix = Matrix3x3::IDENTITY();
        
    };
} // namespace ASEngine


#endif