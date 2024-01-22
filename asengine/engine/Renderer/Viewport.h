#ifndef ASENGINE_VIEWPORT_H
#define ASENGINE_VIEWPORT_H

#include "Core/Singleton/Singleton.h"
#include "Core/Math/vec2.h"
#include "Core/Math/mat3.h"

namespace ASEngine
{
    class Viewport: public Singleton<Viewport>
    {
    public:
        
        // set view port size
        static inline void SetSize(int width, int height) { GetSingleton()->ISetSize(width, height); };

        // get projection matrix
        static inline mat3 GetProjectionMatrix() { return GetSingleton()->m_ProjectionMatrix; };

        // get size
        static inline vec2 GetSize()
        {
            return vec2{(float)GetSingleton()->m_Width, (float)GetSingleton()->m_Height};
        };
    private:
        // set view port size
        void ISetSize(int width, int height);

        // view port size
        int m_Width = -1;
        int m_Height = -1;

        // projection matrix
        mat3 m_ProjectionMatrix = mat3::IDENTITY();
        
    };
} // namespace ASEngine


#endif