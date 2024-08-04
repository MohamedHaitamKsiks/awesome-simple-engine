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
    ASENGINE_SERIALIZE_STRUCT(AudioEngine::Settings, Channels, SampleRate, Outputs);

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

        for (auto& [outputName, output]: audioEngine.m_Outputs)
        {
            std::vector<ResourceRef<AudioPlayer>> audioPlayersToStop = {};

            const auto& players = output.GetPlayers();
            for(const auto& [playerID, player]: players)
            {
                const auto& source = player->GetSource();
                for (uint32_t i = 0; i < frameCount; i++)
                {
                    // check frame index
                    if (player->GetFrameIndex() >= source->GetFrameCount())
                    {
                        if (player->IsLooping())
                        {
                            player->m_FrameIndex = 0;
                        }
                        else
                        {
                            audioPlayersToStop.push_back(player);
                            break;
                        }
                    }

                    // write
                    for (uint32_t j = 0; j < audioEngine.GetChannels(); j++)
                    {
                        buffer[audioEngine.GetChannels() * i + j] += output.GetVolume() * player->GetVolume() * source->GetValue(player->GetFrameIndex() + j, audioEngine.GetChannels());
                    }

                    player->m_FrameIndex++;
                }
            }
            // delete audio playing ids
            for (const auto& audioPlayingID: audioPlayersToStop)
            {
                output.Stop(audioPlayingID);
            }
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
        ASENGINE_ASSERT(settingsFile.Open("assets://audio.settings.json", FileOpenMode::READ), "Cound't open audio.settings.json");

        Json settingsObject = Json::parse(settingsFile.ReadText());
        Serializer::Deserialize(settingsObject, m_Settings);


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

        // create audio outputs
        for (auto outputName: m_Settings.Outputs)
        {
            m_Outputs[outputName];
        }
    }

    void AudioEngine::Terminate()
    {
        // stop all
        m_Outputs.clear();
        ma_device_uninit(&g_Device);
    }

    // play audio
    ResourceRef<AudioPlayer> AudioEngine::Play(UniqueString outputName, const ResourceRef<AudioSource>& source, float volume, bool looping)
    {
        auto& output = m_Outputs[outputName];
        return output.Play(source, volume, looping);
    }

    // stop audio
    void AudioEngine::Stop(const ResourceRef<AudioPlayer>& player)
    {
        for (auto& [outputName, output]: m_Outputs)
        {
            if (output.IsPlaying(player))
            {
                output.Stop(player);
                return;
            }
        }
    }

    // is playing
    bool AudioEngine::IsPlaying(const ResourceRef<AudioPlayer>& player) const
    {
        for (auto& [outputName, output]: m_Outputs)
        {
            if (output.IsPlaying(player))
                return true;
        }
        return false;
    }
} // namespace ASEngine
