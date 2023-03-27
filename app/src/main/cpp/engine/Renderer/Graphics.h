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
#include "Camera.h"

#include "Color.h"
#include "Screen.h"

namespace ASEngine {

	class Graphics {
	public:
		//draw functions
		static void drawRectangle(vec2 position, vec2 size, Color modulate);
		static void drawTexture(Texture texture, vec2 position, vec2 scale, float rotation, Color modulate = Color::white);
		static void drawSprite(SpriteID spriteId, int frame,vec2 position, vec2 scale, float rotation, Color modulate = Color::white);

	private:
		//init quad
		static void quadStart();
		//end quad
		static void quadEnd();


	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_GRAPHICS_H
