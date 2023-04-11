//
// Created by ksiks_wa3r on 4/10/23.
//

#include "CollisionMask.h"

namespace ASEngine {
	CollisionMask CollisionMask::empty = CollisionMask{vec2::zero(), vec2::zero()};


	bool CollisionMask::collideWithMask(CollisionMask &other) {
		return  position.x < other.position.x + other.size.x &&
				position.x + size.x > other.position.x &&
				position.y < other.position.y + other.size.y &&
				size.x + position.y > other.position.y;
	}
} // ASEngine