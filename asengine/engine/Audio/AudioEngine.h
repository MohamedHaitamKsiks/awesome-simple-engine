#ifndef ASENGINE_AUDIO_ENGINE
#define ASENGINE_AUDIO_ENGINE

#include "Thirdparty/miniaudio.h"

#include "Core/Memory/PoolAllocator.h"
#include "Core/Singleton/Singleton.h"
#include "Core/Signals/Signal.h"
#include "Core/Log/Log.h"

#define ASENGINE_AUDIOENGINE_SAMPLE_RATE 48000
#define ASENGINE_AUDIOENGINE_CHANNELS 2

namespace ASEngine
{

    using AudioChannelID = ChunkID;
    struct AudioChannel
    {
        // audio data
        float const* Data = nullptr;
        size_t Size = 0;
        // current audio frame
        size_t FrameIndex = 0;
        // playback volume
        float Volume = 1.0f;
    };
    
    class AudioEngine: public Singleton<AudioEngine>
    {
    
    public:
        // init audio engine
        AudioEngine();

        // uninit audio engine
        ~AudioEngine();

        // audio engine's sample rate
        static constexpr uint32_t GetSampleRate()
        {
            return ASENGINE_AUDIOENGINE_SAMPLE_RATE;
        };

        static constexpr uint32_t GetChannels()
        {
            return ASENGINE_AUDIOENGINE_CHANNELS;
        };

        // fired when a channel finished playing an audio
        inline static Signal<AudioChannelID>& OnAudioFinishedPlaying()
        {
            return GetSingleton()->m_OnAudioFinishedPlaying;
        };  

        // play audio with buffer (volume optional)
        inline static AudioChannelID Play(const float* buffer, size_t size, float volume = 1.0f)
        {
            return GetSingleton()->IPlay(buffer, size, volume);
        };

        // stop by channelID
        inline static void Stop(AudioChannelID channelID)
        {
            GetSingleton()->IStop(channelID);
        }

        // is audio channel valid
        inline static bool IsPlaying(AudioChannelID channelID)
        {
            return !GetSingleton()->m_AudioChannels.IsFree(channelID);
        };

        // set frame for channel
        inline static void SetFrame(AudioChannelID channelID, size_t frame)
        {
            GetSingleton()->m_AudioChannels.Get(channelID).FrameIndex = frame;
        };

        // get current frame in a channel
        inline static size_t GetFrame(AudioChannelID channelID)
        {
            return GetSingleton()->m_AudioChannels.Get(channelID).FrameIndex;
        };

        // set volume for channel
        inline static void SetVolume(AudioChannelID channelID, float volume)
        {
            if (AudioEngine::IsPlaying(channelID))
                GetSingleton()->m_AudioChannels.Get(channelID).Volume = volume;
        };
        
        // get current volume in a channel
        inline static float GetVolume(AudioChannelID channelID)
        {
            return GetSingleton()->m_AudioChannels.Get(channelID).Volume;
        };

    private:
        // audio channels
        TPoolAllocator<AudioChannel> m_AudioChannels{UINT16_MAX};

        // audio device
        ma_device m_Device;

        // on audio play finished
        Signal<AudioChannelID> m_OnAudioFinishedPlaying{};

        // internal functions
        static void MiniAudioDataCallback(ma_device *device, void *output, const void *input, ma_uint32 frameCount);

        AudioChannelID IPlay(const float *buffer, size_t size, float volume);
        void IStop(AudioChannelID channelID);
    };


} // namespace ASEngine


#endif // ASENGINE_AUDIO_ENGINE