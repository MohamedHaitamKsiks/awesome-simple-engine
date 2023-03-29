//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_FONT_H
#define ANDROIDSIMPLEENGINE_FONT_H


#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include "Resource.h"
#include "../Renderer/Texture.h"

/*
 * This font will be monospace for now.
 * */

namespace ASEngine {

	//font caracter
	struct FontCharacter {
		Texture texture;
		int advance;
		int bearingY;
	};

	//font id
	typedef std::string FontID;

	//font resource
	class Font: public Resource {
	public:
		//font data
		FontCharacter fontCharacters[128];
		int size;
		int separation;
		int lineSeparation;
		int spaceSize;

		//load
		static Font load(std::string _name, int _size, std::string fontPath, int _separation, int _lineSeparation, int _spaceSize);
		//add font
		static void add(FontID fontId, Font& font);
		//destroy
		void destroy();

		//equiv between ResourceID and Resource
		//= operator
		Font& operator=(FontID fontId) {
			return Font::fonts[fontId];
		};

		//constructors
		Font() {};
		Font(FontID fontId) {
			*this = Font::fonts[fontId];
		};

	private:
		static std::unordered_map<ResourceID, Font> fonts;

	private:


	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_FONT_H
