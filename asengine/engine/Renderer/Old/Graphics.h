/*
#ifndef ASENGINE_GRAPHICS_H
#define ASENGINE_GRAPHICS_H

#include "engine/Resource/Sprite.h"
#include "engine/Resource/Font.h"

#include "Texture.h"
#include "Camera.h"
#include "Color.h"
#include "Shader.h"
#include "Screen.h"
#include "VertexBufferObject.h"

namespace ASEngine {

	struct GraphicsUniformData {
		Texture texture = Texture{UINT32_MAX};
		bool isSolidColor = false;
		bool firstDraw = false;
	};

	class Graphics {
	public:
		//init graphics
		void init();
		//terminate graphics
		void terminate();
		//draw functions
		//draw rectangle
		void drawRectangle(vec2 position, vec2 size, Color modulate);
		//draw texture
		void drawTexture(Texture texture, vec2 position, vec2 scale, float rotation, Color modulate = Color::WHITE());
		//draw sprite ext
		void drawSprite(const Sprite* sprite, int frame,vec2 position, vec2 scale, float rotation, Color modulate = Color::WHITE());
		//draw sprite
		void drawSprite(const Sprite* sprite, int frame,vec2 position, Color modulate = Color::WHITE());
		//draw text
		void drawText(const std::string& text, vec2 position, const Font* font, Color modulate = Color::WHITE());
		//update graphics
		void update();
	private:
		VertexBufferObject vbo{};
		//uniform data
		//we will save to detect changes
		//changes imply we should submit what we have
		//in the vbo to clear it
		GraphicsUniformData uniformData{};
		//set uniform data
		bool setUniformData(bool isSolidColor, Texture texture);
		//draw vbo
		void draw();


	};

} // ASEngine

#endif //ASENGINE_GRAPHICS_H
*/