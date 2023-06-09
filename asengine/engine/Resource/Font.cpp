//
// Created by ksiks_wa3r on 3/27/23.
//

#include "Font.h"

namespace ASEngine {

	Font Font::load(const std::string& _name, int _size, const std::string& fontPath, int _separation, int _lineSeparation, int _spaceSize) {
		//create font
		Font font{};
		//font image 16x8
		Image fontImage{};
		fontImage.width = FONT_TEXTURE_WIDTH * _size;
		fontImage.height = FONT_TEXTURE_HEIGHT * _size;
		fontImage.format = IMAGE_FORMAT_GRAYSCALE_ALPHA;

		//one character size
		const int subImageBufferSize = 2 * _size * _size * sizeof(char);
		const int imageBufferSize = FONT_TEXTURE_WIDTH * FONT_TEXTURE_WIDTH * subImageBufferSize;

		//allocate image space
		fontImage.pixels = new char[imageBufferSize];
		//fill with 0
		for (int i = 0; i < imageBufferSize; i++)
			fontImage.pixels[i] = 0;

		//init library
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			Log::out("Could not init FreeType Library!!");
			return Font();
		}

		//load font to buffer
		size_t fileLength;

		FT_Byte * buffer = (FT_Byte*) Resource::loadAsBinary(fontPath, &fileLength);

		//craete face
		FT_Face face;
		if (FT_New_Memory_Face(ft, buffer, fileLength, 0, &face)) {
			Log::out("Failed to load font!!");
			return Font();
		}

		//set size
		font.size = _size;
		FT_Set_Pixel_Sizes(face, 0, _size);

		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);

		//generate one pig texture for every character and use
		for (int i = 0; i < 128; i++) {
			//load font char
			if (FT_Load_Char(face, char(i), FT_LOAD_RENDER )) {
				Log::out("Failed to load Glyph!!");
				return Font();
			}

			//bitmapBufferSize
			int bitmapWidth = face->glyph->bitmap.width;
			int bitmapHeight = face->glyph->bitmap.rows;
			int bitmapBufferSize = bitmapWidth * bitmapHeight * sizeof(char) ;

			//image frames
			int hframe = i % FONT_TEXTURE_WIDTH;
			int vframe = i / FONT_TEXTURE_WIDTH;

			//image buffer offset
			int imageBufferOffsetX = hframe * _size;
			int imageBufferOffsetY = vframe * _size;
			//pixels
			//create image where alpha = luminance
			for (int i = 0; i < bitmapBufferSize; i++) {
				//sub image coordinates
				int subImageCoordX = i % bitmapWidth;
				int subImageCoordY = i / bitmapWidth;
				//image coord
				int imageCoordX = subImageCoordX + imageBufferOffsetX;
				int imageCoordY = subImageCoordY + imageBufferOffsetY;
				//pixel
				char pixel = face->glyph->bitmap.buffer[i];
				//get index
				int fontImageIndex = imageCoordX + fontImage.width * imageCoordY;
				fontImage.pixels[2 * fontImageIndex] = 255;
				if (pixel > 100)
					fontImage.pixels[2 * fontImageIndex + 1] = 255;
			}

			//add character
			FontCharacter fontCharacter{
				(int)face->glyph->bitmap.width,
				-face->glyph->bitmap_top,
				hframe,
				vframe
			};
			font.fontCharacters[i] = fontCharacter;

			//font params
			font.separation = _separation;
			font.lineSeparation = _lineSeparation;
			font.spaceSize = _spaceSize;
		}

		//generate texture
		font.texture = Texture::load(fontImage);
		//destroy image
		fontImage.destroy();

		//add font
		Font::add(_name, font);

		//free font data
		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		//free buffer
		delete buffer;
		return font;
	}

	void Font::add(const FontID& fontId, Font &font) {
		font.id = fontId;
		Font::fonts[fontId] = font;
	}

	void Font::importAll() {
		//load json file
		std::string importFontsString = Resource::loadAsText("fonts/import.fonts.json");
		//parse to json
		nlohmann::json importedFonts = nlohmann::json::parse(importFontsString);
		//import all fonts
		for (int i = 0; i < importedFonts.size(); i++) {
			//get font info
			std::string fontName = importedFonts[i]["name"];
			int fontSize = importedFonts[i]["size"];
			std::string fontFilePath = importedFonts[i]["font"];
			int fontSeparation = importedFonts[i]["separation"];
			int fontLineSeparation = importedFonts[i]["lineSeparation"];
			int fontSpaceSize = importedFonts[i]["spaceSize"];
			//load font
			Font::load(fontName, fontSize,"fonts/" + fontFilePath, fontSeparation, fontLineSeparation, fontSpaceSize);
			//log
			Log::out("font loaded");
		}
	}

	void Font::destroy() {
		Font::fonts.erase(id);
	}

	std::unordered_map<ResourceID, Font> Font::fonts = {};

	void Font::terminate() {
		fonts.clear();
	}


} // ASEngine