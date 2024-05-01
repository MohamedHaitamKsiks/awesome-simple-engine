#include "AudioEngine.h"
#include "Core/Log/Log.h"

namespace ASEngine
{
    void AudioEngine::Init()
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
            Debug::Error("Failed to init miniaudio device!");
            return; // Failed to initialize the device.
        }

        // start device
        ma_device_start(&m_Device); // The device is sleeping by default so you'll need to start it manually.
    }

    void AudioEngine::Terminate()
    {
        ma_device_uninit(&m_Device);
    }

    void AudioEngine::MiniAudioDataCallback(ma_device *device, void *output, const void *input, ma_uint32 frameCount)
    {
        // get audio engine
        AudioEngine& engine = AudioEngine::GetInstance();

        // init buffer
        const size_t bufferSize = engine.GetChannels() * frameCount;
        float buffer[bufferSize];

        for (int i = 0; i < bufferSize; i++) buffer[i] = 0.0f;

        // add samples
        for (auto& audioChannel: engine.m_AudioChannels)
        {
            // copy data to buffer
            for (int i = 0; i < frameCount; i++)
            {
                // signal that channel is finished playing song
                if (audioChannel.FrameIndex >= audioChannel.Size) 
                    engine.GetAudioFinishedPlayingSignal().Emit(channelID);

                // stop music if finished (we check twice because the user can change frame index to restart the audio for example)
                if (audioChannel.FrameIndex >= audioChannel.Size)
                {
                    engine.Stop(audioChannel.ID);
                    break;
                }

                // write channels 
                for (int j = 0; j < AudioEngine::GetChannels(); j++)
                {
                    buffer[AudioEngine::GetChannels() * i + j] += audioChannel.Volume * audioChannel.Data[AudioEngine::GetChannels() * audioChannel.FrameIndex + j];
                }
                // move frame index
                audioChannel.FrameIndex++;
            }
            
        }   
        // push data
        memcpy(output, buffer, bufferSize * sizeof(float));
    }

    AudioChannelID AudioEngine::Play(const float *buffer, size_t size, float volume)
    {
        // create channel
        AudioChannel channel;
        channel.Data = buffer;
        channel.Size = size;
        channel.FrameIndex = 0;
        channel.Volume = volume;

        // add channel
        AudioChannelID channelID = m_AudioChannels.Push(channel);
        m_AudioChannels.Get(channelID).ID = channelID;

        return channelID;
    }

    void AudioEngine::Stop(AudioChannelID channelID)
    {
        if (m_AudioChannels.IsFree(channelID)) return;

        m_AudioChannels.Free(channelID);
    }
} // namespace ASEngine
