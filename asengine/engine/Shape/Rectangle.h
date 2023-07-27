

#ifndef ASENGINE_RECTANGLE_H
#define ASENGINE_RECTANGLE_H

#include "engine/Math/vec2.h"

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

#endif //ASENGINE_RECTANGLE_H
