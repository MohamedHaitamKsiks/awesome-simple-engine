#include "AudioOutput.h"

namespace ASEngine
{
    ResourceRef<AudioPlayer> AudioOutput::Play(const ResourceRef<AudioSource>& source, float volume, bool looping)
    {
        ResourceRef<AudioPlayer> player = AudioPlayer::GetResourceClass().New();
        player->Create(source, volume, looping);

        m_Players[player->GetResourceID()] = player;

        return player;
    }

    void AudioOutput::Stop(const ResourceRef<AudioPlayer>& player)
    {
        ASENGINE_ASSERT(IsPlaying(player), "Audio playing id is not currently playing!");
        m_Players.erase(player->GetResourceID());
    }

    void AudioOutput::SetVolume(float volume)
    {
        m_Volume = volume;
    }

} // namspace ASEngine
