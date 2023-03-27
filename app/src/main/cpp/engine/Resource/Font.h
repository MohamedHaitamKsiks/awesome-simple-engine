//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_FONT_H
#define ANDROIDSIMPLEENGINE_FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Resource.h"

/*
 * This font will be monospace for now.
 * */

namespace ASEngine {

	class Font: public Resource {
	public:
		//font data
		Texture texture;
		int size;

		//load font


	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_FONT_H
