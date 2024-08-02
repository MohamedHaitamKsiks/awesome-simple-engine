#ifndef __ASENGINE_AUDIO_OUTPUT_H
#define __ASENGINE_AUDIO_OUTPUT_H

#include "Audio/AudioPlayer/AudioPlayer.h"
#include "Resource/ResourceID.h"
#include "Resource/ResourceRef.h"
#include <unordered_map>

namespace ASEngine
{
    class AudioOutput
    {
    public:
        AudioOutput() {}
        ~AudioOutput() {}

        // porhibite copy
        AudioOutput(const AudioOutput&) = delete;
        AudioOutput& operator=(const AudioOutput&) = delete;

        // play audio
        ResourceRef<AudioPlayer> Play(const ResourceRef<AudioSource>& source, float volume = 1.0f, bool looping = false);

        // stop
        void Stop(const ResourceRef<AudioPlayer>& player);

        // is playing
        inline bool IsPlaying(const ResourceRef<AudioPlayer>& player) const
        {
            return m_Players.find(player->GetResourceID()) != m_Players.end();
        }

        // get players
        inline const std::unordered_map<ResourceID, ResourceRef<AudioPlayer>>& GetPlayers() const
        {
            return m_Players;
        }

        // set volume
        void SetVolume(float volume);

        // get volume
        inline float GetVolume() const
        {
            return m_Volume;
        }
    private:
        std::unordered_map<ResourceID, ResourceRef<AudioPlayer>> m_Players{};
        float m_Volume = 1.0f;
    };
} // namespace ASEngine

#endif // __ASENGINE_AUDIO_OUTPUT_H
