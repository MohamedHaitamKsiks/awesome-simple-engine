//
// Created by ksiks_wa3r on 4/10/23.
//

#ifndef ANDROIDSIMPLEENGINE_COLLISIONMASK_H
#define ANDROIDSIMPLEENGINE_COLLISIONMASK_H

#include "../Math/vec2.h"

namespace ASEngine {

	struct CollisionMask {
		//collision mask desciption
		vec2 size;
		vec2 position;
		//default empty collision mask
		static CollisionMask empty;

		// check collision with other mask
		bool collideWithMask(CollisionMask& other);
		// check outsize collision mask(act like boundaries)
		bool collideWithBound(CollisionMask& bound);

	};


} // ASEngine

#endif //ANDROIDSIMPLEENGINE_COLLISIONMASK_H
