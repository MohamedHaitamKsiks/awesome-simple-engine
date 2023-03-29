//
// Created by ksiks_wa3r on 3/27/23.
//

#include "Font.h"

namespace ASEngine {

	Font Font::load(std::string _name, int _size, std::string fontPath, int _separation, int _lineSeparation, int _spaceSize) {
		//create font
		Font font{};

		//init library
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			ALOG("Could not init FreeType Library!!");
			return Font();
		}

		//load font to buffer
		//open asset
		AAsset* asset = AAssetManager_open(assetManager, fontPath.c_str(), AASSET_MODE_BUFFER);

		// Get the length of the file using AAsset_getLength.
		off_t fileLength = AAsset_getLength(asset);

		// Read the contents of the file using AAsset_read.
		FT_Byte * buffer = new stbi_uc[fileLength];
		int bytesRead = AAsset_read(asset, buffer, fileLength);

		//craete face
		FT_Face face;
		if (FT_New_Memory_Face(ft, buffer, fileLength, 0, &face)) {
			ALOG("Failed to load font!!");
			return Font();
		}

		//set size
		font.size = _size;
		FT_Set_Pixel_Sizes(face, 0, _size);


		//generate texture for each character
		//I'm aware this solution is very bad
		//I'll fix it later to put all the textures in one big texture
		for (int i = 0; i < 128; i++) {
			if (FT_Load_Char(face, char(i), FT_LOAD_RENDER )) {
				ALOG("Failed to load Glyph!!");
				return Font();
			}

			//create Image
			Image image{};
			image.width = face->glyph->bitmap.width;
			image.height = face->glyph->bitmap.rows;

			int bitmapBufferSize = image.width * image.height * sizeof(stbi_uc) ;

			//pixels
			//create image where alpha = luminance
			image.pixels = new stbi_uc[2 * bitmapBufferSize];
			for (int i = 0; i < bitmapBufferSize; i++) {
				stbi_uc pixel = face->glyph->bitmap.buffer[i];
				image.pixels[2 * i] = 255;
				image.pixels[2 * i + 1] = pixel;
			}

			//image format
			image.format = IMAGE_FORMAT_GRAYSCALE_ALPHA;

			//generate texture
			Texture texture = Texture::load(image);

			//destroy image
			image.destroy();

			//add character
			FontCharacter fontCharacter{
				texture,
				face->glyph->advance.x / 64, // advance is on 64th of a pixel
				-face->glyph->bitmap_top
			};
			font.fontCharacters[i] = fontCharacter;

			//font params
			font.separation = _separation;
			font.lineSeparation = _lineSeparation;
			font.spaceSize = _spaceSize;
		}

		//add font
		Font::add(_name, font);

		//free font data
		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		//free buffer
		AAsset_close(asset);
		delete buffer;

		return font;
	}

	void Font::add(FontID fontId, Font &font) {
		font.id = fontId;
		Font::fonts[fontId] = font;
	}

	void Font::destroy() {
		Font::fonts.erase(id);
	}

	std::unordered_map<ResourceID, Font> Font::fonts = {};


} // ASEngine