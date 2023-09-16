#include "TextRenderingSystem2D.h"

void TextRenderingSystem2D::OnCreate()
{
	// insert code ...
};

void TextRenderingSystem2D::OnUpdate(float delta)
{
	// insert code ...
};

void TextRenderingSystem2D::OnRender2D()
{
	ForEach([](TextRenderer2D& textRenderer, Transform2D& transform)
	{
		// get font
		const auto& font = ResourceManager<Font>::Get(textRenderer.FontID);
		vec2 fontSize
		{
			(float) font.GetSize(),
			(float) font.GetSize()
		};
		ResourceID fontMaterialID = font.GetDefaultMaterialID();

		// transform matrix
		mat3 transformMatrix = mat3::Transform(transform.Position, transform.Scale, transform.Rotation);

		// pointer relative position
		vec2 cursorPosition = vec2::ZERO();

		// draw characters
		for (int i = 0; i < textRenderer.Text.length(); i++)
		{
			char c = textRenderer.Text[i];
			
			switch(c)
			{
			// draw space
			case ' ':
				cursorPosition.x += font.GetSpaceSize();
				break;
			// go back to line
			case '\n':
				cursorPosition.x = 0.0f;
				cursorPosition.y += (float) font.GetLineSeparation();
				break;
			// draw normal char	
			default:
				const auto &fontCharacter = font.GetFontCharacterOf(c);

				// calculate character position
				vec2 characterPosition{
					0.0f,
					(float) fontCharacter.BearingY
				};
				mat3 characterTransformMatrix = transformMatrix * mat3::Translate(cursorPosition + characterPosition);

				// draw quyad
				Quad2D quad
				{
					fontSize,
					characterTransformMatrix,
					textRenderer.Modulate,
					fontCharacter.HFrame, FONT_TEXTURE_WIDTH,
					fontCharacter.VFrame, FONT_TEXTURE_HEIGHT
				};
				Renderer2D::DrawQuad(quad, fontMaterialID);
		
				// move cursor
				cursorPosition.x += (float) fontCharacter.Width + font.GetSeparation();

			}
			
		}
	});
};

void TextRenderingSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
