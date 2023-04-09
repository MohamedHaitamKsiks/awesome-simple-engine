//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_GRAPHICS_H
#define ANDROIDSIMPLEENGINE_GRAPHICS_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "../log.h"
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
		static void init();
		//draw functions
		//draw rectangle
		static void drawRectangle(vec2 position, vec2 size, Color modulate);
		//draw texture
		static void drawTexture(Texture texture, vec2 position, vec2 scale, float rotation, Color modulate = Color::white);
		//draw sprite ext
		static void drawSprite(SpriteID spriteId, int frame,vec2 position, vec2 scale, float rotation, Color modulate = Color::white);
		//draw sprite
		static void drawSprite(SpriteID spriteId, int frame,vec2 position, Color modulate = Color::white);
		//draw text
		static void drawText(std::string text, vec2 position, FontID fontId, Color modulate = Color::white);
		//update graphics
		static void update();
	private:
		static VertexBufferObject vbo;
		//uniform data
		//we will save to detect changes
		//changes imply we should submit what we have
		//in the vbo to clear it
		static GraphicsUniformData uniformData;
		//set uniform data
		static bool setUniformData(bool isSolidColor, Texture texture);
		//draw vbo
		static void draw();


	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_GRAPHICS_H
