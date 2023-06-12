//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_FONT_H
#define ANDROIDSIMPLEENGINE_FONT_H


#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <sstream>

#include "../FileSystem/File.h"
#include "../Renderer/Texture.h"
#include "../Thirdparty/json.hpp"
#include "../Log/Log.h"

#define FONT_TEXTURE_WIDTH 16
#define FONT_TEXTURE_HEIGHT 8

/*
 * This font will be monospace for now.
 * */

namespace ASEngine {

	//font caracter
	struct FontCharacter {
		int width;
		int bearingY;
		int hframe;
		int vframe;
	};

	//font resource
	class Font {
	public:
		//font data
		FontCharacter fontCharacters[128];
		//font size
		int size = -1;
		//font character seperation size
		int separation = -1;
		//font line seperation
		int lineSeparation = -1;
		//font space size
		int spaceSize = -1;
		// font texture
		Texture texture;

		//load font from file
		bool load(const std::string &fontPath, int _size, int _separation, int _lineSeparation, int _spaceSize);

		//destructor
		~Font();
	
	private:
		
	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_FONT_H
