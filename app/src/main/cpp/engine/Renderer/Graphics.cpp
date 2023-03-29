//
// Created by ksiks_wa3r on 3/27/23.
//

#include "Graphics.h"

namespace ASEngine {

	void Graphics::quadDraw() {
		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
	}

	void Graphics::drawTexture(Texture texture, vec2 position, vec2 scale, float rotation, Color modulate) {
		//1 frame
		Material::current.setShaderParam("hframe", 0);
		Material::current.setShaderParam("hframes", 1);
		Material::current.setShaderParam("vframe", 0);
		Material::current.setShaderParam("vframes", 1);

		//is solid
		Material::current.setShaderParam("isSolidColor", false);

		//modulate
		Material::current.setShaderParam("modulate", modulate);

		//transform matrix
		vec2 imageScale = vec2{ (float)texture.width(), (float)texture.height() };
		mat3 transform =
				mat3::translate(position) *
				mat3::rotation(rotation) *
				mat3::scale(scale) *
				mat3::scale(imageScale);

		Material::current.setShaderParam("transform", transform);

		quadDraw();
	}

	void Graphics::drawSprite(SpriteID spriteId, int frame, vec2 position, vec2 scale, float rotation, Color modulate) {

		//get sprite
		Sprite sprite = spriteId;
		//1 frame
		Material::current.setShaderParam("hframe", frame % sprite.frames);
		Material::current.setShaderParam("hframes", sprite.frames);
		Material::current.setShaderParam("vframe", 0);
		Material::current.setShaderParam("vframes", 1);

		//is solid
		Material::current.setShaderParam("isSolidColor", false);

		//modulate
		Material::current.setShaderParam("modulate", modulate);

		//transform matrix
		vec2 imageScale = vec2{ (float)sprite.width, (float)sprite.height };
		mat3 transform =
				mat3::translate(position) *
				mat3::rotation(rotation) *
				mat3::scale(scale) *
				mat3::translate( vec2{-sprite.offset.x, -sprite.offset.y} ) *
				mat3::scale(imageScale) ;

		Material::current.setShaderParam("transform", transform);

		//pass texture
		Material::current.setShaderParam("texture", sprite.texture);

		quadDraw();

	}

	void Graphics::drawRectangle(vec2 position, vec2 size, Color modulate) {

		//1 frame
		Material::current.setShaderParam("hframe", 0);
		Material::current.setShaderParam("hframes", 1);
		Material::current.setShaderParam("vframe", 0);
		Material::current.setShaderParam("vframes", 1);

		//is solid
		Material::current.setShaderParam("isSolidColor", true);

		//modulate
		Material::current.setShaderParam("modulate", modulate);

		//transform matrix
		mat3 transform =
				mat3::translate(position) *
				mat3::scale(size);

		Material::current.setShaderParam("transform", transform);

		quadDraw();
	}

	void Graphics::drawText(std::string text, vec2 position, FontID fontId, Color modulate) {
		return;
		//get font
		Font font(fontId);

		//1 frame
		Material::current.setShaderParam("hframe", 0);
		Material::current.setShaderParam("hframes", 1);
		Material::current.setShaderParam("vframe", 0);
		Material::current.setShaderParam("vframes", 1);


		//draw every character
		vec2 cursorPosition = vec2::zero();
		for (auto c: text) {
			//transform matrix
			FontCharacter fontCharacter = font.fontCharacters[c];
			Texture texture = fontCharacter.texture;

			//image scale
			vec2 imageScale = vec2{ (float)texture.width(), (float)texture.height() };
			//charcter position
			vec2 characterPosition = vec2{
				0.0f,
				(float)(fontCharacter.bearingY)
			};

			//transform
			mat3 transform =
					mat3::translate(position + cursorPosition + characterPosition) *
					mat3::scale(imageScale) ;

			Material::current.setShaderParam("transform", transform);

			//pass texture
			Material::current.setShaderParam("texture", texture);

			//move cursor
			switch (c) {
				case ' ':
					cursorPosition.x += (float)(font.spaceSize);
					break;
				case '\n':
					cursorPosition.x = 0.0f;
					cursorPosition.y += (float) (texture.height() + font.lineSeparation );
					break;
				default:
					cursorPosition.x += (float)(texture.width() + font.separation);
					quadDraw(); //draw

			}

		}
	}
} // ASEngine