#ifndef __ASENGINE_LAYER_2D_H
#define __ASENGINE_LAYER_2D_H

#include <vector>
#include <unordered_map>

#include "2D/Font/Font.h"
#include "2D/Quad2D/Quad2D.h"
#include "2D/Sprite/Sprite.h"

#include "Core/Math/Matrix3x3.h"
#include "Core/Math/Vector2.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Color.h"
#include "Renderer/Material/Material.h"



#include "Resource/ResourceRef.h"

#define _ASENGINE_QUAD_MAX_COUNT 16383

namespace ASEngine
{
    enum class TextHorizontalAlign
    {
        LEFT,
        CENTER,
        RIGHT
    };

    enum class TextVerticalAlign
    {
        TOP,
        MIDDLE,
        BOTTOM
    };


    // layer 2D
    class  Layer2D
    {
    public:
        Layer2D() {}
        ~Layer2D() {}

        // porhibit copy
        Layer2D(const Layer2D&) = delete;
        Layer2D& operator=(const Layer2D&) = delete;

        // draw quad 2d to layer
        void DrawQuad2D(const Quad2D& quad2D, const ResourceRef<Material>& material);

        // draw quad 2d and return it to
        Quad2D& DrawQuad2D(const ResourceRef<Material>& material);

        // draw sprite
        inline void DrawSprite(const ResourceRef<Sprite>& sprite, const Matrix3x3& transform, uint32_t hframe, uint32_t vframe, const Color& modulate)
        {
            DrawSprite(sprite, transform, hframe, vframe, modulate, sprite->GetMaterial());
        }

        // draw sprite with custom material
        void DrawSprite(const ResourceRef<Sprite>& sprite, const Matrix3x3& transform, uint32_t hframe, uint32_t vframe, const Color& modulate, const ResourceRef<Material>& material);

        // draw fill rectangle
        void DrawFillRectangle(const Vector2& size, const Matrix3x3& transform, const Color& color);

        // draw line
        void DrawLine(const Vector2& start, const Vector2& end, float lineThickness, const Matrix3x3& transform, const Color& color);

        // draw line using material
        void DrawLine(const Vector2& start, const Vector2& end, float lineThickness, const Matrix3x3& transform, const Color& color, const ResourceRef<Material>& material);

        // draw text
        inline void DrawText(const ResourceRef<Font>& font, const std::string text, const Matrix3x3& transform, const Color& color)
        {
            DrawText(font, text, transform, color, font->GetSprite()->GetMaterial());
        }

        // draw text with material
        void DrawText(const ResourceRef<Font>& font, const std::string text, const Matrix3x3& transform, const Color& color, const ResourceRef<Material>& material);

        // draw text with align
        void DrawTextAlign(const ResourceRef<Font>& font, const std::string text, const Matrix3x3& transform, TextHorizontalAlign horizontalAlign, TextVerticalAlign verticalAlign, const Color& color)
        {
            DrawTextAlign(font, text, transform, horizontalAlign, verticalAlign, color, font->GetSprite()->GetMaterial());
        }

        // draw text with align and material
        void DrawTextAlign(const ResourceRef<Font>& font, const std::string text, const Matrix3x3& transform, TextHorizontalAlign horizontalAlign, TextVerticalAlign verticalAlign, const Color& color, const ResourceRef<Material>& material);

    protected:
        friend class Renderer2D;

        // init layer
        void Init();

        // draw layer
        void Draw(const Matrix3x3& cameraTranform, const Matrix3x3& viewportTransform, bool pixelSnapping);

    private:
        // quad 2d command with material
        struct Quad2DCommand
        {
            Quad2DCommand() = default;
            ~Quad2DCommand() {};

            Quad2D Quads2D[_ASENGINE_QUAD_MAX_COUNT];
            size_t Count = 0;

            ResourceRef<Material> Mat = ResourceRef<Material>::NONE();
        };

        // quad queue
        std::vector<Quad2DCommand> m_Quad2DCommands = {};

        ResourceRef<Material> m_CurrentMaterial = ResourceRef<Material>::NONE();
        Quad2DCommand* m_CurrentCommand = nullptr;

        // unifrom buffer names
        UniqueString m_Renderer2DName;
        UniqueString m_CameraTransformName;
        UniqueString m_ViewportTransfromName;
        UniqueString m_PixelSnappingName;

        // vbo
        ResourceRef<Buffer> m_VertexBuffer = ResourceRef<Buffer>::NONE();
        ResourceRef<Buffer> m_IndexBuffer = ResourceRef<Buffer>::NONE();
    };
} // namespace ASEngine


#endif // __ASENGINE_LAYER_2D_H
