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
#include "../Thirdparty/json.hpp"

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
		Texture texture;

		//load
		static Font load(const std::string& _name, int _size, const std::string& fontPath, int _separation, int _lineSeparation, int _spaceSize);
		static void importAll();
		//terminate all
		static void terminate();
		//add font
		static void add(const FontID& fontId, Font& font);
		//destroy
		void destroy();

		//equiv between ResourceID and Resource
		//= operator
		Font& operator=(const FontID& fontId) {
			return Font::fonts[fontId];
		};

		//constructors
		Font() {};
		Font(const FontID& fontId) {
			*this = Font::fonts[fontId];
		};

	private:
		static std::unordered_map<ResourceID, Font> fonts;


	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_FONT_H
