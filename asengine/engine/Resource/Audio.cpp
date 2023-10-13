#include "Audio.h"

namespace ASEngine
{   
    Audio::~Audio()
    {
        if (m_Data)
        {
            delete[] m_Data;
            m_Data = nullptr;
        }
    }

    bool Audio::Load(const std::string& path)
    {
        // open file
        File audioFile;
        audioFile.Open(path, FileOpenMode::READ);

        // read audio data
        const size_t size = audioFile.GetSize();
        uint8_t* buffer = new uint8_t[size];

        audioFile.Read((char*) buffer);

        // create audio decoder for wav
        ma_decoder decoder;
        ma_decoder_config decoderConfig = ma_decoder_config_init(ma_format_f32, AudioEngine::GetChannels(), AudioEngine::GetSampleRate());
        decoderConfig.encodingFormat = ma_encoding_format_wav;

        ma_result result = ma_decoder_init_memory(buffer, size, &decoderConfig, &decoder);
        if (result != MA_SUCCESS)
        {
            return false; // Failed to read data from the decoder.
        }

        // get audio length
        ma_decoder_get_length_in_pcm_frames(&decoder, (ma_uint64*)&m_Size);

        // create buffer for audio
        m_Data = new float[AudioEngine::GetChannels() * m_Size];
        ma_decoder_read_pcm_frames(&decoder, (void *)m_Data, (ma_uint64) m_Size, NULL);

        // destroy decoder
        ma_decoder_uninit(&decoder);

        // delete file buffer
        delete buffer;

        return true;
    }
} // namespace ASEngine
