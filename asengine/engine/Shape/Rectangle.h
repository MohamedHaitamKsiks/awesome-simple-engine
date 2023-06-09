//
// Created by ksiks_wa3r on 4/16/23.
//

#ifndef ANDROIDSIMPLEENGINE_RECTANGLE_H
#define ANDROIDSIMPLEENGINE_RECTANGLE_H

#include "../Math/vec2.h"

namespace ASEngine {

	struct Rectangle {
		vec2 size = {0.0f, 0.0f};
		vec2 position = {0.0f, 0.0f};

		// check intersection with other Rectangle
		bool intersectWith(Rectangle& other);

		// check point inside rectangle
		bool pointInside(vec2 point);
	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_RECTANGLE_H
