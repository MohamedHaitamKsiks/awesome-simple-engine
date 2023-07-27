
#include "Font.h"

namespace ASEngine {

	bool Font::Load(const std::string &fontPath, int size, int separation, int lineSeparation, int spaceSize)
	{
		
		int width = FONT_TEXTURE_WIDTH * size;
		int height = FONT_TEXTURE_HEIGHT * size;
		ImageFormat format = ImageFormat::GRAYSCALE_ALPHA;

		//one character size
		const int subImageBufferSize = 2 * size * size * sizeof(char);
		const int imageBufferSize = FONT_TEXTURE_WIDTH * FONT_TEXTURE_WIDTH * subImageBufferSize;

		//allocate image space
		uint8_t* pixels = new uint8_t[imageBufferSize];

		//fill with 0
		for (int i = 0; i < imageBufferSize; i++)
			pixels[i] = 0;

		//init library
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			Debug::Log("Could not init FreeType Library!!");
			return false;
		}

		//load font from file
		File fontFile;
		fontFile.Open(fontPath, FileOpenMode::READ);
		
		size_t fileLength = fontFile.GetSize();
		FT_Byte buffer[fileLength];
		fontFile.Read((char*) buffer);
		
		fontFile.Close();

		//craete face
		FT_Face face;
		if (FT_New_Memory_Face(ft, buffer, fileLength, 0, &face)) {
			Debug::Log("Failed to load font!!");
			return false;
		}

		FT_Set_Pixel_Sizes(face, 0, size);

		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);

		//generate one pig texture for every character and use
		for (int i = 0; i < FONT_CHARACTER_NUMBER; i++) {
			//load font char
			if (FT_Load_Char(face, char(i), FT_LOAD_RENDER )) {
				Debug::Log("Failed to load Glyph!!");
				return false;
			}

			//bitmapBufferSize
			int bitmapWidth = face->glyph->bitmap.width;
			int bitmapHeight = face->glyph->bitmap.rows;
			int bitmapBufferSize = bitmapWidth * bitmapHeight * sizeof(char) ;

			//image frames
			int hframe = i % FONT_TEXTURE_WIDTH;
			int vframe = i / FONT_TEXTURE_WIDTH;

			//image buffer offset
			int imageBufferOffsetX = hframe * size;
			int imageBufferOffsetY = vframe * size;
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
				int fontImageIndex = imageCoordX + width * imageCoordY;
				pixels[2 * fontImageIndex] = char(255);
				pixels[2 * fontImageIndex + 1] = pixel;

			}

			//add character
			FontCharacter fontCharacter {
				(int)face->glyph->bitmap.width,
				-face->glyph->bitmap_top,
				hframe,
				vframe
			};
			m_FontCharacters[i] = fontCharacter;

		}

		// font params
		m_Size = size;
		m_Separation = separation;
		m_LineSeparation = lineSeparation;
		m_SpaceSize = spaceSize;

		//generate texture
		Image image = Image(pixels, width, height, format);
		m_Texture = Texture::LoadFromImage(image);

		//free font data
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	
		return true;
	}

	Font::~Font() 
	{
		if (m_Texture != TEXTURE_NULL)
			m_Texture.Destroy();
	}

} // ASEngine