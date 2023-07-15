
#ifndef ASENGINE_FONT_H
#define ASENGINE_FONT_H


#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <sstream>

#include "Resource.h"
#include "ResourceManager.h"

#include "engine/FileSystem/File.h"
#include "engine/Renderer/Texture.h"
#include "engine/Thirdparty/json.hpp"
#include "engine/Log/Log.h"

#define FONT_TEXTURE_WIDTH 16
#define FONT_TEXTURE_HEIGHT 8

/*
 * This font will be monospace for now.
 * */

namespace ASEngine {

	//font caracter
	struct FontCharacter {
		int width = -1;
		int bearingY = -1;
		int hframe = 0;
		int vframe = 0;
	};

	//font resource
	class Font : public Resource {

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
		Texture texture = Texture::defaultTexture;

		//load font from file
		bool load(const std::string &fontPath, int _size, int _separation, int _lineSeparation, int _spaceSize);

		// import all fonts
		static void importAll();

		// destructor
		~Font();
	
	private:
		
	};

} // ASEngine

#endif //ASENGINE_FONT_H
