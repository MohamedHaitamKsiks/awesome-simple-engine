#include "AudioModule.h"

#include "Audio/AudioPlayer/AudioPlayer.h"
#include "AudioEngine/AudioEngine.h"
#include "AudioSource/AudioSource.h"

#include "Resource/ResourceManager.h"

#include "ECS/SystemManager.h"

namespace ASEngine
{
    void AudioModule::Init()
    {
        ASENGINE_REGISTER_RESOURCE_CLASS(AudioSource);
        ASENGINE_REGISTER_RESOURCE_CLASS(AudioPlayer);
        ASENGINE_REGISTER_SYSTEM(AudioEngine);
    }
} // namspace ASEngine
