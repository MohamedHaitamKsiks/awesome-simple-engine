//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_GRAPHICS_H
#define ANDROIDSIMPLEENGINE_GRAPHICS_H

#include "../Resource/Material.h"
#include "../Resource/Sprite.h"
#include "../Resource/Font.h"
#include "Camera.h"
#include "Color.h"
#include "Screen.h"

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
		void drawTexture(Texture texture, vec2 position, vec2 scale, float rotation, Color modulate = Color::white);
		//draw sprite ext
		void drawSprite(const SpriteID& spriteId, int frame,vec2 position, vec2 scale, float rotation, Color modulate = Color::white);
		//draw sprite
		void drawSprite(const SpriteID& spriteId, int frame,vec2 position, Color modulate = Color::white);
		//draw text
		void drawText(const std::string& text, vec2 position, const FontID& fontId, Color modulate = Color::white);
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

#endif //ANDROIDSIMPLEENGINE_GRAPHICS_H
