#ifndef __ASENGINE_AUDIO_ENGINE_H
#define __ASENGINE_AUDIO_ENGINE_H

#include "Audio/AudioSource/AudioSource.h"

#include "Core/Memory/ChunkID.h"
#include "Core/Memory/PoolAllocator.h"
#include "Core/Singleton/Singleton.h"

#include "ECS/System.h"

#include "Resource/ResourceRef.h"

#include <unordered_set>

namespace ASEngine
{
    using AudioPlayingID = ChunkID;

    // main audio system
    class AudioEngine: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(AudioEngine);
    private:
        // audio play info
        struct AudioPlayingInfo
        {
            ResourceRef<AudioSource> Source = ResourceRef<AudioSource>::NONE();
            size_t FrameIndex = 0;
            float Volume = 1.0f;
            bool IsLooping = false;
        };
    public:

        // settings
        struct Settings
        {
            uint32_t Channels = 2;
            uint32_t SampleRate = 48000;
        };

        ~AudioEngine() {}

        // get channels
        inline uint32_t GetChannels() const
        {
            return m_Settings.Channels;
        }

        // get sample rate
        inline uint32_t GetSampleRate() const
        {
            return m_Settings.SampleRate;
        }

        // play audio
        AudioPlayingID Play(const ResourceRef<AudioSource>& source, float volume = 1.0f, bool looping = false);

        // stop audio
        void Stop(AudioPlayingID audioPlayingID);

        // is playing
        bool IsPlaying(AudioPlayingID audioPlayingID) const
        {
            return !m_PlayingInfos.IsFree(audioPlayingID);
        }

        // get volume
        inline float GetVolume(AudioPlayingID audioPlayingID) const
        {
            return m_PlayingInfos.Get(audioPlayingID).Volume;
        }

        // set volume
        inline void SetVolume(AudioPlayingID audioPlayingID, float volume)
        {
            m_PlayingInfos.Get(audioPlayingID).Volume = volume;
        }

        // get current frame
        inline size_t GetCurrentFrameIndex(AudioPlayingID audioPlayingID) const
        {
            return m_PlayingInfos.Get(audioPlayingID).FrameIndex;
        }

    private:
        // audio settings
        Settings m_Settings{};

        // audio playing
        PoolAllocator<AudioPlayingInfo> m_PlayingInfos{};
        std::unordered_set<AudioPlayingID> m_PlayingIDs = {};

        // get list of audio playings
        inline const std::unordered_set<AudioPlayingID>& GetAudioPlayinIDs() const
        {
            return m_PlayingIDs;
        }


        friend void AudioDataCallback(void *output, const void *input, uint32_t frameCount);

        void Init() override;
        void Terminate() override;
    };
} // namespace ASEngine

#endif // __ASENGINE_AUDIO_ENGINE_H
