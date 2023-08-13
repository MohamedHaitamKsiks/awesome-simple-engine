
#ifndef ASENGINE_FONT_H
#define ASENGINE_FONT_H


#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <cstdint>
#include <sstream>

#include "Core/Serialization/Serializer.h"
#include "Core/FileSystem/File.h"
#include "Core/Log/Log.h"

#include "Renderer/Texture.h"

#include "Resource.h"

#define FONT_TEXTURE_WIDTH 16
#define FONT_TEXTURE_HEIGHT 8
#define FONT_CHARACTER_NUMBER 128


namespace ASEngine 
{

	using FontID = ResourceID;

	//font caracter
	struct FontCharacter 
	{
		int Width = -1;
		int BearingY = -1;
		int HFrame = 0;
		int VFrame = 0;
	};

	//font resource
	class Font : public Resource
	{

	public:
		Font() {};
		~Font();

		//load font from file
		bool Load(const std::string &fontPath, int size, int separation, int lineSeparation, int spaceSize);

		// get character info at
		inline FontCharacter GetFontCharacterOf(char c) const 
		{ 
			return m_FontCharacters[(size_t) c];
		};

		// get size
		inline int GetSize() const {return m_Size;};

		// get separation
		inline int GetSeparation() const {return m_Separation;};

		// get line separation
		inline int GetLineSeparation() const {return m_LineSeparation;};

		// get space size
		inline int GetSpaceSize() const {return m_SpaceSize;};

		// get texture
		inline Texture GetTexture() const {return m_Texture;};

	
	private:
		// font path
		UniqueString m_FontPath;
		// font texture
		Texture m_Texture = TEXTURE_NULL;
		// font data
		FontCharacter m_FontCharacters[FONT_CHARACTER_NUMBER];
		// font size
		int m_Size = -1;
		// font character seperation size
		int m_Separation = -1;
		// font line seperation
		int m_LineSeparation = -1;
		// font space size
		int m_SpaceSize = -1;
	};

} // ASEngine

#endif //ASENGINE_FONT_H
