#include "RectangleRenderingSystem2D.h"

void RectangleRenderingSystem2D::OnCreate()
{
	// one pixel white
	uint32_t* whitePixels = new uint32_t[1];
	whitePixels[0] = UINT32_MAX;

	// create image 1x1 white
	Image image{(uint8_t*) whitePixels, 1, 1, ImageFormat::RGBA};

	// create texture 1x1 white
	Texture texture = Texture::LoadFromImage(image);

	// get default shader
	ResourceID defaultShaderID = ResourceManager<Shader>::GetResourceId(UniqueString("shaders/default.glsl"));
	Debug::Log("toz");

	// create material 
	ResourceID defaultMaterialID = ResourceManager<Material>::Add();

	auto& defaultMaterial = ResourceManager<Material>::Get(defaultMaterialID);
	defaultMaterial.Create(defaultShaderID);
	defaultMaterial.SetShaderParam(UniqueString("u_Texture"), texture);

	// save material ID
	RectangleRenderer2D::DefaultMaterialID = defaultMaterialID;
}

void RectangleRenderingSystem2D::OnUpdate(float delta)
{
	// insert code ...
};

void RectangleRenderingSystem2D::OnRender2D()
{
	ForEach([](RectangleRenderer2D &rectangle, Transform2D &transform)
		{
		// get transform matrix
		mat3 transformMatrix = mat3::Transform(transform.Position, transform.Scale, transform.Rotation);

		// draw quad
		Quad2D quad{rectangle.Size, transformMatrix, rectangle.Modulate};
		Renderer2D::DrawQuad(quad, RectangleRenderer2D::DefaultMaterialID); 
	});
};

void RectangleRenderingSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
