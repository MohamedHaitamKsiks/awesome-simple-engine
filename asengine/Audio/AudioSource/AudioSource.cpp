#include "AudioSource.h"

#include "Audio/AudioEngine/AudioEngine.h"
#include "Core/Error/Assertion.h"
#include "Core/FileSystem/File.h"
#include "Core/Memory/ByteBuffer.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

#include "Resource/ResourceRefSerialization.h"
#include "Resource/ResourceSerialization.h"

#include <miniaudio.h>

ASENGINE_SERIALIZE_RESOURCE_REF(AudioSource);

namespace ASEngine
{
    template <>
    void Serializer::Deserialize(const Json& object, AudioSource& dest)
    {
        std::string path;
        Serializer::Deserialize(object.at("Path"), path);

        dest.Create(path);
    }

    template <>
    Json Serializer::Serialize(const AudioSource& value)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(AudioSource);

    void AudioSource::Create(const std::string& path)
    {
        // open file
        File audioFile;
        ASENGINE_ASSERT(audioFile.Open(path, FileOpenMode::READ), "Coudn't open file");

        ByteBuffer audioFileBuffer;
        audioFile.Read(audioFileBuffer);

        audioFile.Close();

        // get audio settings
        uint32_t audioChannels = AudioEngine::GetInstance().GetChannels();
        uint32_t audioSampleRate = AudioEngine::GetInstance().GetSampleRate();

        // create audio decoder to for wav
        ma_decoder decoder;
        ma_decoder_config decoderConfig = ma_decoder_config_init(ma_format_f32, audioChannels, audioSampleRate);
        decoderConfig.encodingFormat = ma_encoding_format_wav;

        ma_result result =  ma_decoder_init_memory(audioFileBuffer.GetData(), audioFileBuffer.GetSize(), &decoderConfig, &decoder);
        ASENGINE_ASSERT(result == MA_SUCCESS, "Cound't decode wav file");

        // get audio length
        ma_decoder_get_length_in_pcm_frames(&decoder, (ma_uint64*)&m_FrameCount);
        m_Size = m_FrameCount * audioChannels;
        m_Duration = static_cast<float>(m_FrameCount) / static_cast<float>(audioSampleRate);

        // create buffer for audio
        m_Data = std::make_unique<float[]>(m_Size);
        ma_decoder_read_pcm_frames(&decoder, reinterpret_cast<void*>(m_Data.get()), static_cast<ma_uint64>(m_Size), nullptr);

        // destroy decoder
        ma_decoder_uninit(&decoder);
    }

    float AudioSource::GetValue(size_t frameIndex, uint32_t channel) const
    {
        if (frameIndex > m_FrameCount)
            return 0.0f;

        return m_Data[AudioEngine::GetInstance().GetChannels() * frameIndex + channel];
    }
} // namespace ASEngine
