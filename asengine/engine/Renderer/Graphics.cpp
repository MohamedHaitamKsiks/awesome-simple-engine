//
// Created by ksiks_wa3r on 3/27/23.
//

#include "Graphics.h"

namespace ASEngine {

	//init vertex buffer
	void Graphics::init() {
		vbo.create();
	}

	//terminate vertex buffer
	void Graphics::terminate() {
		vbo.destroy();
	}

	void Graphics::drawTexture(Texture texture, vec2 position, vec2 scale, float rotation, Color modulate) {
		//set unifrom data
		setUniformData(false, texture);

		//transform matrix
		vec2 imageScale = vec2{ (float)texture.width(), (float)texture.height() };
		mat3 transform =
				mat3::translate(position) *
				mat3::rotation(rotation) *
				mat3::scale(scale);

		//create the quad
		Quad quad = Quad::create(imageScale, transform, 0.0f, modulate);
		vbo.addQuad(quad);

	}

	void Graphics::drawSprite(const Sprite& sprite, int frame, vec2 position, vec2 scale, float rotation, Color modulate) {
		//set unifrom data
		setUniformData(false, sprite.texture);

		//transform matrix
		vec2 imageScale = vec2{ (float)sprite.width, (float)sprite.height };
		mat3 transform =
				mat3::transform(position, scale, rotation) *
				mat3::translate( vec2{-sprite.offset.x, -sprite.offset.y} );

		//create the quad
		Quad quad = Quad::create(imageScale, transform, 0.0f,
								 modulate,
								 frame % sprite.frames, sprite.frames, 0, 1);
		vbo.addQuad(quad);

	}

	void Graphics::drawSprite(const Sprite& sprite, int frame, vec2 position, Color modulate) {
		//set unifrom data
		setUniformData(false, sprite.texture);
		//transform matrix
		vec2 imageScale = vec2{ (float)sprite.width, (float)sprite.height };
		//create the quad
		Quad quad = Quad::create(imageScale, position - sprite.offset, 0.0f,
								 modulate,
								 frame % sprite.frames, sprite.frames, 0, 1);
		vbo.addQuad(quad);
	}


	void Graphics::drawRectangle(vec2 position, vec2 size, Color modulate) {
		//set unifom
		setUniformData(true, Texture::defaultTexture);
		//create the quad
		Quad quad = Quad::create(size, position, 0.0f, modulate);
		vbo.addQuad(quad);
	}

	void Graphics::drawText(const std::string& text, vec2 position, const Font& font, Color modulate) 
	{
		Texture texture = font.texture;
		setUniformData(false, texture);

		//draw every character
		vec2 cursorPosition = vec2::zero();
		for (auto c: text) {
			//test character
			switch (c) {
				case ' ':
					cursorPosition.x += (float)(font.spaceSize);
					continue;
				case '\n':
					cursorPosition.x = 0.0f;
					cursorPosition.y += (float) (font.size + font.lineSeparation );
					continue;
			}
			//transform matrix
			FontCharacter fontCharacter = font.fontCharacters[c];

			//image scale
			vec2 imageScale = vec2{
				(float)texture.width() / FONT_TEXTURE_WIDTH,
				(float)texture.height() / FONT_TEXTURE_HEIGHT
			};
			//charcter position
			vec2 characterPosition = vec2{
				0.0f,
				(float)(fontCharacter.bearingY)
			};

			//add quad
			Quad textQuad = Quad::create(imageScale,
										 position + cursorPosition + characterPosition, 0.0f,
										 modulate,
										 fontCharacter.hframe, FONT_TEXTURE_WIDTH,
										 fontCharacter.vframe, FONT_TEXTURE_HEIGHT);
			vbo.addQuad(textQuad);

			//move cursor
			cursorPosition.x += (float)(fontCharacter.width + font.separation);

		}

	}

	int drawCalls = 0;

	void Graphics::update() {
		draw();
		uniformData.firstDraw = false;
		drawCalls = 0;
	}

	bool Graphics::setUniformData(bool isSolidColor, Texture texture) {
		if (isSolidColor != uniformData.isSolidColor || texture.id != uniformData.texture.id) {
			if (uniformData.firstDraw)
				draw();
			//save uniform data
			uniformData.isSolidColor = isSolidColor;
			uniformData.texture = texture;
		}
		uniformData.firstDraw = true;
		return false;
	}



	void Graphics::draw() {
		//set unifrom data
		Shader::getCurrent().getShaderParam("isSolidColor").setValue((int) uniformData.isSolidColor);
		//pass texture
		Shader::getCurrent().getShaderParam("texture").setValue(uniformData.texture);
		//bind vertex attribute
		Vertex::bindAttributes(Shader::getCurrent().glProgram);
		//draw remaning quads
		vbo.bind();
		vbo.pushData();
		vbo.draw();
		drawCalls++;

		
		
	}


} // ASEngine