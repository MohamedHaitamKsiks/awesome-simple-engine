#include "AudioPlayer2D.h"

EXPORT(AudioPlayer2D, AudioName, AutoPlaying, Volume)

void AudioPlayer2D::OnCreate()
{
    AudioID = ResourceManager<Audio>::GetResourceId(AudioName);

    if (AutoPlaying) Play();

}

void AudioPlayer2D::Play()
{
    // stop if is playing
    if (IsPlaying()) Stop();
    

    // get audio
    const auto& audio = ResourceManager<Audio>::Get(AudioID);
    
    // start playing 
    AudioEngine::Play(audio.GetData(), audio.GetSize(), Volume);
}
