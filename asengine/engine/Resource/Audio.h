#ifndef ASENGINE_AUDIO_H
#define ASENGINE_AUDIO_H

#include "Thirdparty/miniaudio.h"
#include "Core/FileSystem/File.h"

#include "Audio/AudioEngine.h"

#include "Resource.h"


namespace ASEngine
{
    class Audio: public Resource
    {

    public:
        ~Audio();

        // load by path (.wav only now)
        bool Load(const std::string& path);

        // get data
        inline float* GetData() const
        {
            return m_Data;
        }

        // get size
        inline size_t GetSize() const
        {
            return m_Size;
        }

    private:
        float* m_Data = nullptr;
        size_t m_Size = 0;
    };
} // namespace ASEngine1


#endif // ASENGINE_AUDIO_H