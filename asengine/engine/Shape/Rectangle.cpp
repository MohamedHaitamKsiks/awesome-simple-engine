
#include "Rectangle.h"

namespace ASEngine {

	bool Rectangle::intersectWith(Rectangle &other) {
		return  position.x < other.position.x + other.size.x &&
				position.x + size.x > other.position.x &&
				position.y < other.position.y + other.size.y &&
				size.x + position.y > other.position.y;
	}

	bool Rectangle::pointInside(vec2 point) {
		return 	point.x > position.x &&
				point.x < position.x + size.x &&
				point.y > position.y &&
				point.y < position.y + size.y;
	}
} // ASEngine