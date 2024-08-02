#include "AudioPlayer.h"

namespace ASEngine
{
    void AudioPlayer::Create(const ResourceRef<AudioSource>& source, float volume, bool isLooping)
    {
        m_Source = source;
        SetVolume(volume);
        SetIsLooping(isLooping);
        SetFrameIndex(0);
    }

    void AudioPlayer::SetVolume(float volume)
    {
        m_Volume = volume;
    }

    void AudioPlayer::SetIsLooping(bool isLooping)
    {
        m_IsLooping = isLooping;
    }

    void AudioPlayer::SetFrameIndex(size_t frameIndex)
    {
        m_FrameIndex = frameIndex;
    }
} // namspace ASEngine
