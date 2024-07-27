#include "Layer2D.h"

#include "2D/Quad2D/Quad2D.h"
#include "2D/Renderer2D/Renderer2D.h"
#include "Core/Math/Vector2.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Renderer.h"
#include "Resource/ResourceRef.h"
#include <memory>


#define _ASENGINE_QUAD_INDEX_COUNT 6

namespace ASEngine
{
    void Layer2D::Init()
    {
        auto& bufferClass = Buffer::GetResourceClass();

        // create index buffer for quads [0, 1, 2, 2, 3, 0]
        m_IndexBuffer = bufferClass.New();

        uint32_t localIndices[] = {0, 1, 2, 2, 3, 0};
        std::unique_ptr<uint32_t[]> indexBufferData = std::make_unique<uint32_t[]>(_ASENGINE_QUAD_MAX_COUNT * _ASENGINE_QUAD_INDEX_COUNT);

        for (size_t i = 0; i < _ASENGINE_QUAD_MAX_COUNT; i++)
        {
            for (size_t j = 0; j < _ASENGINE_QUAD_INDEX_COUNT; j++)
            {
                indexBufferData[i * _ASENGINE_QUAD_INDEX_COUNT + j] = localIndices[j] + i * 4;
            }
        }

        m_IndexBuffer->Create(BufferType::INDEX);
        m_IndexBuffer->SetData(indexBufferData.get(), _ASENGINE_QUAD_MAX_COUNT * _ASENGINE_QUAD_INDEX_COUNT * sizeof(uint32_t));

        // create vertex buffer
        m_VertexBuffer = bufferClass.New();
        m_VertexBuffer->Create(BufferType::ARRAY);

        // cache names
        m_Renderer2DName = UniqueString("Renderer2D");
        m_CameraTransformName = UniqueString("CameraTransform");
        m_ViewportTransfromName = UniqueString("ViewportTransform");
    }

    void Layer2D::DrawQuad2D(const Quad2D &quad2D, const ResourceRef<Material>& material)
    {
        Quad2D& createdQuad2D = DrawQuad2D(material);
        createdQuad2D = quad2D;
    }

    Quad2D& Layer2D::DrawQuad2D(const ResourceRef<Material>& material)
    {
        // submit
        if (material != m_CurrentMaterial || !m_CurrentCommand || m_CurrentCommand->Count >= _ASENGINE_QUAD_MAX_COUNT)
        {
            m_CurrentCommand = &m_Quad2DCommands.emplace_back();

            m_CurrentCommand->Count = 0;

            m_CurrentMaterial = material;
            m_CurrentCommand->Mat = material;
        }

        // queue quad
        Quad2D& quad2D = m_CurrentCommand->Quads2D[m_CurrentCommand->Count];
        m_CurrentCommand->Count++;

        return quad2D;
    }

    void Layer2D::DrawSprite(const ResourceRef<Sprite>& sprite, const Matrix3x3& transform, uint32_t hframe, uint32_t vframe, const Color& modulate, const ResourceRef<Material>& material)
    {
        Quad2D& quad2D = DrawQuad2D(material);
        sprite->CreateQuad2D(quad2D, transform, hframe, vframe, modulate);
    }

    void Layer2D::DrawFillRectangle(const Vector2& size, const Matrix3x3& transform, const Color& color)
    {
        Quad2D& quad2D = DrawQuad2D(Renderer2D::GetInstance().GetFillRectangleDefaultMaterial());
        quad2D.Create(size, transform, color, Vector2::ZERO(), Vector2::ONE());
    }

    void Layer2D::DrawText(const ResourceRef<Font>& font, const std::string text, const Matrix3x3& transform, const Color& color, const ResourceRef<Material>& material)
    {
        Vector2 cursorPosition = Vector2::ZERO();
        for (auto character: text)
        {
            auto& characterInfo = font->GetCharacterInfo(character);


            // return to line
            if (character == '\n')
            {
                cursorPosition.x = 0.0f;
                cursorPosition.y += static_cast<float>(font->GetLineSeparation() + font->GetSize());
                continue;
            }
            // space
            else if (character == ' ')
            {
                cursorPosition.x += static_cast<float>(font->GetSpaceSize());
                continue;
            }

            Quad2D& quad2D = DrawQuad2D(material);
            font->GetSprite()->CreateQuad2D(quad2D, transform, characterInfo.HFrame, characterInfo.VFrame, color,
                cursorPosition + Vector2(0.0f, static_cast<float>(font->GetSize()) - static_cast<float>(characterInfo.BearingY)) );

            cursorPosition.x += static_cast<float>(characterInfo.Width + font->GetCharacterSeparation());
        }
    }


    void Layer2D::Draw(const Matrix3x3& cameraTranform, const Matrix3x3& viewportTransform)
    {
        auto& renderer = Renderer::GetInstance();

        for (auto& quad2DCommand: m_Quad2DCommands)
        {
            // bind material
            quad2DCommand.Mat->SetShaderParam(m_Renderer2DName, m_CameraTransformName, cameraTranform);
            quad2DCommand.Mat->SetShaderParam(m_Renderer2DName, m_ViewportTransfromName, viewportTransform);

            renderer.BindMaterial(quad2DCommand.Mat);

            // send quads data
            m_VertexBuffer->SetData(quad2DCommand.Quads2D, quad2DCommand.Count * sizeof(Quad2D));

            // draw call
            renderer.BindVertexBuffer(m_VertexBuffer, 0);
            renderer.BindIndexBuffer(m_IndexBuffer);

            renderer.DrawElements(quad2DCommand.Count * _ASENGINE_QUAD_INDEX_COUNT);

        }

        // reset command buffer
        m_CurrentCommand = nullptr;
        m_CurrentMaterial = ResourceRef<Material>::NONE();

        m_Quad2DCommands.clear();
    }

} // namespace ASEngine
