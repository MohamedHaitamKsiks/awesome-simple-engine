#ifndef __ASENGINE_AUDIO_PLAYER_H
#define __ASENGINE_AUDIO_PLAYER_H

#include "Audio/AudioSource/AudioSource.h"
#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"
#include "Resource/ResourceRef.h"

namespace ASEngine
{
    // responsible for playing audios, created
    class AudioPlayer: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(AudioPlayer);
    public:
        ~AudioPlayer() {}


        void SetVolume(float volume);
        inline float GetVolume() const
        {
            return m_Volume;
        }

        void SetIsLooping(bool isLooping);
        inline bool IsLooping() const
        {
            return m_IsLooping;
        }

        inline const ResourceRef<AudioSource>& GetSource() const
        {
            return m_Source;
        }

        void SetFrameIndex(size_t frameIndex);
        inline size_t GetFrameIndex() const
        {
           return m_FrameIndex;
        }

    protected:
        friend class AudioOutput;

        // create audio player for a source
        void Create(const ResourceRef<AudioSource>& source, float volume = 1.0f, bool isLooping = false);

        private:
        ResourceRef<AudioSource> m_Source = ResourceRef<AudioSource>::NONE();
        size_t m_FrameIndex = 0;
        float m_Volume = 1.0f;
        bool m_IsLooping = false;

        friend void AudioDataCallback(void *output, const void *input, uint32_t frameCount);
    };
} // namespace ASEngine

#endif // __ASENGINE_AUDIO_PLAYER_H
