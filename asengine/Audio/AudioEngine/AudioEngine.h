#ifndef __ASENGINE_AUDIO_ENGINE_H
#define __ASENGINE_AUDIO_ENGINE_H

#include "Audio/AudioOutput/AudioOutput.h"
#include "Audio/AudioPlayer/AudioPlayer.h"
#include "Audio/AudioSource/AudioSource.h"

#include "Core/Singleton/Singleton.h"

#include "Core/String/UniqueString.h"
#include "ECS/System.h"

#include "Resource/ResourceRef.h"

#include <unordered_map>
#include <unordered_set>

namespace ASEngine
{
    // main audio system
    class AudioEngine: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(AudioEngine);
    public:
        // settings
        struct Settings
        {
            uint32_t Channels = 2;
            uint32_t SampleRate = 48000;
            std::vector<UniqueString> Outputs{};
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

        // get output
        inline AudioOutput& GetAudioOuput(UniqueString outputName)
        {
            return m_Outputs.at(outputName);
        }

        // play audio
        ResourceRef<AudioPlayer> Play(UniqueString outputName, const ResourceRef<AudioSource>& source, float volume = 1.0f, bool looping = false);

        // stop audio
        void Stop(const ResourceRef<AudioPlayer>& player);

        // is playing
        bool IsPlaying(const ResourceRef<AudioPlayer>& player) const;

    private:
        // audio settings
        Settings m_Settings{};

        // audio playing
        std::map<UniqueString, AudioOutput> m_Outputs = {};

        friend void AudioDataCallback(void *output, const void *input, uint32_t frameCount);

        void Init() override;
        void Terminate() override;
    };
} // namespace ASEngine

#endif // __ASENGINE_AUDIO_ENGINE_H
