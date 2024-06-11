#ifndef __ASENGINE_AUDIO_ENGINE
#define __ASENGINE_AUDIO_ENGINE

/*
#include "Thirdparty/miniaudio.h"

#include "Core/Memory/PoolAllocator.h"
#include "Core/Singleton/Singleton.h"
#include "Core/Signals/Signal.h"

#include "ECS/System.h"

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
        // channel id
        AudioChannelID ID = 0;
    };
    
    class AudioEngine: public ISystem
    {
    
    public:
        // init audio engine
        Init();

        // uninit audio engine
        Terminate();

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
        inline Signal<AudioChannelID>& GetAudioFinishedPlayingSignal()
        {
            return m_OnAudioFinishedPlaying;
        };  

        // play audio with buffer (volume optional)
        AudioChannelID Play(const float* buffer, size_t size, float volume = 1.0f);

        // stop by channelID
        void Stop(AudioChannelID channelID);

        // is audio channel valid
        bool IsPlaying(AudioChannelID channelID)
        {
            return !m_AudioChannels.IsFree(channelID);
        }

        // set frame for channel
        inline void SetFrame(AudioChannelID channelID, size_t frame)
        {
            m_AudioChannels.Get(channelID).FrameIndex = frame;
        }

        // get current frame in a channel
        inline size_t GetFrame(AudioChannelID channelID)
        {
            return Geinline tSingleton()->m_AudioChannels.Get(channelID).FrameIndex;
        }

        // set volume for channel
        inline void SetVolume(AudioChannelID channelID, float volume)
        {
            if (IsPlaying(channelID))
            {
                GetSingleton()->m_AudioChannels.Get(channelID).Volume = volume;
            }
        }
        
        // get current volume in a channel
        inline float GetVolume(AudioChannelID channelID)
        {
            return m_AudioChannels.Get(channelID).Volume;
        }

    private:
        // audio channels
        PoolAllocator<AudioChannel> m_AudioChannels{UINT16_MAX};

        // audio device
        ma_device m_Device;

        // on audio play finished
        Signal<AudioChannelID> m_OnAudioFinishedPlaying{};

        // internal functions
        static void MiniAudioDataCallback(ma_device *device, void *output, const void *input, ma_uint32 frameCount);
    };


} // namespace ASEngine
*/

#endif // __ASENGINE_AUDIO_ENGINE