#include "AudioEngine.h"


namespace ASEngine
{
    AudioEngine::AudioEngine()
    {
        // mini audio device config
        ma_device_config config = ma_device_config_init(ma_device_type_playback);
        config.playback.format = ma_format_f32; // Set to ma_format_unknown to use the device's native format.
        config.playback.channels = ASENGINE_AUDIOENGINE_CHANNELS;           // Set to 0 to use the device's native channel count.
        config.sampleRate = ASENGINE_AUDIOENGINE_SAMPLE_RATE; // Set to 0 to use the device's native sample rate.

        config.dataCallback = &MiniAudioDataCallback;    // This function will be called when miniaudio needs more data.
        // init device
        if (ma_device_init(NULL, &config, &m_Device) != MA_SUCCESS)
        {
            Debug::Log("Failed to init miniaudio device!");
            return; // Failed to initialize the device.
        }

        // start device
        ma_device_start(&m_Device); // The device is sleeping by default so you'll need to start it manually.
    }

    AudioEngine::~AudioEngine()
    {
        ma_device_uninit(&m_Device);
    }

    void AudioEngine::MiniAudioDataCallback(ma_device *device, void *output, const void *input, ma_uint32 frameCount)
    {

        // get audio engine
        AudioEngine* engine = AudioEngine::GetSingleton();

        // return if singleton not true
        if (!engine) return;

        // init buffer
        const size_t bufferSize = ASENGINE_AUDIOENGINE_CHANNELS * frameCount;
        float buffer[bufferSize];

        for (int i = 0; i < bufferSize; i++) buffer[i] = 0.0f;

        // add samples
        for (AudioChannelID channelID = 0; channelID < engine->m_AudioChannels.GetCapacity(); channelID++)
        {
            if (engine->m_AudioChannels.IsFree(channelID)) continue;

            // get audio channel
            AudioChannel& audioChannel = engine->m_AudioChannels.Get(channelID);

            // copy data to buffer
            for (int i = 0; i < frameCount; i++)
            {
                // signal that channel is finished playing song
                if (audioChannel.FrameIndex >= audioChannel.Size) 
                    engine->OnAudioFinishedPlaying().Emit(channelID);

                // stop music if finished (we check twice because the user can change frame index to restart the audio for example)
                if (audioChannel.FrameIndex >= audioChannel.Size)
                {
                    engine->IStop(channelID);
                    break;
                }

                // write channels 
                for (int j = 0; j < ASENGINE_AUDIOENGINE_CHANNELS; j++)
                {
                    buffer[ASENGINE_AUDIOENGINE_CHANNELS * i + j] += audioChannel.Data[ASENGINE_AUDIOENGINE_CHANNELS * audioChannel.FrameIndex + j];
                }
                // move frame index
                audioChannel.FrameIndex++;
            }
            
        }   
        // push data
        memcpy(output, buffer, bufferSize * sizeof(float));
    }

    AudioChannelID AudioEngine::IPlay(const float *buffer, size_t size, float volume)
    {
        // create channel
        AudioChannel channel;
        channel.Data = buffer;
        channel.Size = size;
        channel.FrameIndex = 0;
        channel.Volume = volume;

        // add channel
        AudioChannelID channelID = m_AudioChannels.Push(channel);
        return channelID;
    }

    void AudioEngine::IStop(AudioChannelID channelID)
    {
        m_AudioChannels.Free(channelID);
    }
} // namespace ASEngine
