#include "AudioEngine.h"
#include "Core/Error/Assertion.h"
#include "Core/FileSystem/File.h"
#include "Core/Serialization/SerializeStruct.h"
#include "Core/Serialization/Serializer.h"

#include <cstring>
#include <miniaudio.h>
#include <vector>


namespace ASEngine
{
    ASENGINE_SERIALIZE_STRUCT(AudioEngine::Settings, Channels, SampleRate);

    // save ma device as static variable since AudioEngine is a singleton.
    // It's not a memeber of the class since i don't want to add miniaudio to the header files of the engine
    static ma_device g_Device;

    // miniaudio callback
    void AudioDataCallback(void *output, const void *input, uint32_t frameCount)
    {
        if (!AudioEngine::IsInstantiated())
            return;

        AudioEngine& audioEngine = AudioEngine::GetInstance();

        // init buffer for frames
        size_t bufferSize = audioEngine.GetChannels() * frameCount;
        float buffer[bufferSize];

        // init buffer
        for (size_t i = 0; i < bufferSize; i++)
            buffer[i] = 0.0f;

        // add to buffer
        const auto& audioPlayingIDs = audioEngine.GetAudioPlayinIDs();
        std::vector<AudioPlayingID> audioPlayingIDsToDelete = {};

        for(AudioPlayingID audioPlayingID: audioPlayingIDs)
        {
            auto& audioPlayingInfo = audioEngine.m_PlayingInfos.Get(audioPlayingID);

            for (uint32_t i = 0; i < frameCount; i++)
            {
                // check frame index
                if (audioPlayingInfo.FrameIndex >= audioPlayingInfo.Source->GetFrameCount())
                {
                    if (audioPlayingInfo.IsLooping)
                    {
                        audioPlayingInfo.FrameIndex = 0;
                    }
                    else
                    {
                        audioPlayingIDsToDelete.push_back(audioPlayingID);
                        break;
                    }
                }

                // write
                for (uint32_t j = 0; j < audioEngine.GetChannels(); j++)
                {
                    const auto& audioSourceData = audioPlayingInfo.Source->GetData();
                    buffer[audioEngine.GetChannels() * i + j] += audioPlayingInfo.Volume * audioSourceData[audioEngine.GetChannels() * audioPlayingInfo.FrameIndex + j];
                }

                audioPlayingInfo.FrameIndex++;
            }
        }

        // delete audio playing ids
        for (AudioPlayingID audioPlayingID: audioPlayingIDsToDelete)
        {
            audioEngine.Stop(audioPlayingID);
        }

        // data to output
        memcpy(output, buffer, sizeof(float) * bufferSize);
    }

    void MiniAudioDataCallback(ma_device *device, void *output, const void *input, ma_uint32 frameCount)
    {
        AudioDataCallback(output, input, static_cast<uint32_t>(frameCount));
    }


    void AudioEngine::Init()
    {
        // load settings
        File settingsFile;
        ASENGINE_ASSERT(settingsFile.Open("audio.settings.json", FileOpenMode::READ), "Cound't open audio.settings.json");

        Json settingsObject = Json::parse(settingsFile.ReadText());
        Serializer::Deserialize(settingsObject, m_Settings);

        settingsFile.Close();

        // mini audio device config
        ma_device_config config = ma_device_config_init(ma_device_type_playback);
        config.playback.format = ma_format_f32; // Set to ma_format_unknown to use the device's native format.
        config.playback.channels = m_Settings.Channels;           // Set to 0 to use the device's native channel count.
        config.sampleRate = m_Settings.SampleRate; // Set to 0 to use the device's native sample rate.

        config.dataCallback = &MiniAudioDataCallback;    // This function will be called when miniaudio needs more data.

        // init device
        ASENGINE_ASSERT(ma_device_init(nullptr, &config, &g_Device) == MA_SUCCESS, "Cound't initialize audio device!");
        // start device
        ma_device_start(&g_Device); // The device is sleeping by default so you'll need to start it manually.
    }

    void AudioEngine::Terminate()
    {
        // stop all
        m_PlayingInfos.Clear();
        ma_device_uninit(&g_Device);
    }

    AudioPlayingID AudioEngine::Play(const ResourceRef<AudioSource>& source, float volume, bool looping)
    {
        // craete audio playin
        AudioPlayingID audioPlayingID = m_PlayingInfos.Allocate();

        AudioPlayingInfo& audioPlayingInfo = m_PlayingInfos.Get(audioPlayingID);
        audioPlayingInfo.FrameIndex = 0;
        audioPlayingInfo.Volume = volume;
        audioPlayingInfo.IsLooping = looping;
        audioPlayingInfo.Source = source;

        // add audio playing id
        m_PlayingIDs.insert(audioPlayingID);

        return audioPlayingID;
    }

    void AudioEngine::Stop(AudioPlayingID audioPlayingID)
    {
        ASENGINE_ASSERT(IsPlaying(audioPlayingID), "Audio playing id is not currently playing!");

        m_PlayingIDs.erase(audioPlayingID);
        m_PlayingInfos.Free(audioPlayingID);
    }
} // namespace ASEngine
