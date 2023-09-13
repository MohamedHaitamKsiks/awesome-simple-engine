#include "SpriteRenderingSystem2D.h"

void SpriteRenderingSystem2D::OnUpdate(float delta)
{
	ForEach([&delta](SpriteRenderer2D &sprite, Transform2D &transform)
	{
		sprite.Frame += delta * sprite.FrameRate;
		if (sprite.Frame > (float) sprite.Frames)
			sprite.Frame -= (float) sprite.Frames;
	});
};

void SpriteRenderingSystem2D::OnRender2D()
{
	ForEach([](SpriteRenderer2D &sprite, Transform2D &transform)
	{
		// get transform matrix
		mat3 transformMatrix = mat3::Transform(transform.Position + sprite.Offset, transform.Scale, transform.Rotation);
		// center
		if (sprite.Centered) transformMatrix = transformMatrix * mat3::Translate( sprite.Size * -0.5f);

		// draw quad
		Quad2D quad{sprite.Size, transformMatrix, sprite.Modulate, (int) sprite.Frame, (int) sprite.Frames, 0, 1};
		Renderer2D::DrawQuad(quad, sprite.MaterialID); 
	});
};

void SpriteRenderingSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
