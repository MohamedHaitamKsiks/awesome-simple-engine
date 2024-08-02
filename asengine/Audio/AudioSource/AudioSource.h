#ifndef __ASENGINE_AUDIO_SOURCE_H
#define __ASENGINE_AUDIO_SOURCE_H

#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"
#include "Resource/ResourceSerialization.h"

#include <memory>

namespace ASEngine
{
    class AudioSource: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(AudioSource);
    ASENGINE_SERIALIZE_RESOURCE(AudioSource);
    public:
        ~AudioSource() {}

        // create audio with .wav path
        void Create(const std::string& path);

        // get duration in seconds
        inline float GetDuration() const
        {
            return m_Duration;
        }

        // get value at frame / channle
        float GetValue(size_t frameIndex, uint32_t channel) const;

    protected:
        // get data
        inline const std::unique_ptr<float[]>& GetData() const
        {
            return m_Data;
        }

        // get buffer size
        inline size_t GetSize() const
        {
            return m_Size;
        }

        // get frame count
        inline size_t GetFrameCount() const
        {
            return m_FrameCount;
        }

        friend class AudioEngine;
        friend void AudioDataCallback(void *output, const void *input, uint32_t frameCount);
    private:
        std::unique_ptr<float[]> m_Data = nullptr;
        size_t m_Size = 0;
        size_t m_FrameCount = 0;
        float m_Duration = 0.0f;
    };
} // namespace ASEngine

#endif // __ASENGINE_AUDIO_SOURCE_H
