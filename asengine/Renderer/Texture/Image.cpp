#include "Image.h"
#include "stb_image.h"
#include "Core/Error/Assertion.h"
#include "Core/FileSystem/File.h"
#include "Core/Debug/Debug.h"

#define ASENGINE_IMAGE_CHANNELS 4

namespace ASEngine 
{

    Image::Image(int width, int height)
    {
        m_Pixels = ByteBuffer(width * height * ASENGINE_IMAGE_CHANNELS);
    }

    Image::Image(const std::string &path)
    {
        //read image file
        File imageFile;
        if(!imageFile.Open(path, FileOpenMode::READ)) 
        {
            Debug::Error("Cannot open image:", path);
            return;
        }

        size_t fileLength = imageFile.GetSize();
        ByteBuffer fileBuffer{};
        imageFile.Read(fileBuffer);
        imageFile.Close();

        //decode
        stbi_uc* pixels = stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(fileBuffer.GetData()), static_cast<int>(fileLength), &m_Width, &m_Height, &m_Channels, STBI_rgb_alpha);
        ASENGINE_ASSERT(pixels, "");

        m_Pixels.SetData(pixels, m_Width * m_Height * ASENGINE_IMAGE_CHANNELS);
    }

    Color Image::GetPixelAt(int x, int y) const
    {
        size_t offset = (y * m_Height + x) * ASENGINE_IMAGE_CHANNELS;
        const auto *data = reinterpret_cast<const uint8_t *>(m_Pixels.GetData());

        Color color{};
        color.r = static_cast<float>(data[offset]) / 255.0f;
        color.g = static_cast<float>(data[offset + 1]) / 255.0f;
        color.b = static_cast<float>(data[offset + 2]) / 255.0f;
        color.a = static_cast<float>(data[offset + 3]) / 255.0f;

        return color;
    }

    void Image::SetPixelAt(int x, int y, const Color &color)
    {
        uint8_t byteColor[ASENGINE_IMAGE_CHANNELS];
        byteColor[0] = static_cast<uint8_t>(color.r * 255.0f);
        byteColor[1] = static_cast<uint8_t>(color.g * 255.0f);
        byteColor[2] = static_cast<uint8_t>(color.b * 255.0f);
        byteColor[3] = static_cast<uint8_t>(color.a * 255.0f);

        m_Pixels.SetDataAt(byteColor, sizeof(byteColor), (y * m_Height + x) * ASENGINE_IMAGE_CHANNELS);
    }

} // ASEngine