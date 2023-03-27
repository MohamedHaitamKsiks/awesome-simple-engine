//
// Created by ksiks_wa3r on 3/27/23.
//

#include "Graphics.h"

namespace ASEngine {

	void Graphics::quadStart() {
		//get position attribute
		int vPosition = glGetAttribLocation(Material::current.glProgram, "vPosition");
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(vPosition);
		//get texture coordinates attribute
		int vTextureCoord = glGetAttribLocation(Material::current.glProgram, "vTextureCoord");
		glVertexAttribPointer(vTextureCoord, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(vTextureCoord);
		//pass view
		Material::current.setShaderParam("view", Screen::getView());
		//pass camera
		Material::current.setShaderParam("camera", Camera::current->getMatrix());
	}

	void Graphics::quadEnd() {
		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
	}

	void Graphics::drawTexture(Texture texture, vec2 position, vec2 scale, float rotation, Color modulate) {
		quadStart();
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

		quadEnd();
	}

	void Graphics::drawSprite(SpriteID spriteId, int frame, vec2 position, vec2 scale, float rotation, Color modulate) {
		//get sprite
		Sprite sprite = spriteId;

		//draw
		quadStart();
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

		quadEnd();

	}

	void Graphics::drawRectangle(vec2 position, vec2 size, Color modulate) {
		quadStart();
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

		quadEnd();
	}
} // ASEngine