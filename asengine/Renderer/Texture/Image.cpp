#include "Image.h"
#include "stb_image.h"
#include "Core/Error/Assertion.h"
#include "Core/FileSystem/File.h"
#include "Core/Debug/Debug.h"

#define ASENGINE_IMAGE_CHANNELS 4

namespace ASEngine
{

    void Image::Create(uint32_t width, uint32_t height)
    {
        m_Pixels = ByteBuffer(width * height * ASENGINE_IMAGE_CHANNELS);
        m_Width = width;
        m_Height = height;
    }

    void Image::LoadPNG(const std::string &path)
    {
        // read image file
        File imageFile;
        ASENGINE_ASSERT(imageFile.Open(path, FileOpenMode::READ), "Couldn't load image");

        size_t fileLength = imageFile.GetSize();
        ByteBuffer fileBuffer{};
        imageFile.Read(fileBuffer);

        // decode
        stbi_uc *pixels = stbi_load_from_memory(reinterpret_cast<const stbi_uc *>(fileBuffer.GetData()), static_cast<int>(fileLength), &m_Width, &m_Height, &m_Channels, STBI_rgb_alpha);
        ASENGINE_ASSERT(pixels, "Coudn't load image");

        m_Pixels.Move(pixels, m_Width * m_Height * ASENGINE_IMAGE_CHANNELS);
    }

    Color Image::GetPixelAt(uint32_t x, uint32_t y) const
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

    void Image::SetPixelAt(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        uint8_t byteColor[ASENGINE_IMAGE_CHANNELS];
        byteColor[0] = r;
        byteColor[1] = g;
        byteColor[2] = b;
        byteColor[3] = a;

        m_Pixels.SetDataAt(byteColor, sizeof(byteColor), (y * m_Width + x) * ASENGINE_IMAGE_CHANNELS);
    }

    void Image::SetPixelAt(uint32_t x, uint32_t y, const Color &color)
    {
        uint8_t byteColor[ASENGINE_IMAGE_CHANNELS];
        byteColor[0] = static_cast<uint8_t>(color.r * 255.0f);
        byteColor[1] = static_cast<uint8_t>(color.g * 255.0f);
        byteColor[2] = static_cast<uint8_t>(color.b * 255.0f);
        byteColor[3] = static_cast<uint8_t>(color.a * 255.0f);

        m_Pixels.SetDataAt(byteColor, sizeof(byteColor), (y * m_Width + x) * ASENGINE_IMAGE_CHANNELS);
    }

} // ASEngine
