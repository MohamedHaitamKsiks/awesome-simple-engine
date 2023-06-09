//
// Created by ksiks_wa3r on 3/27/23.
//
#include "Color.h"

namespace ASEngine {

	//colors implementation
	Color Color::white = Color{1.0f, 1.0f, 1.0f, 1.0f};
	Color Color::red = Color{1.0f, 0.0f, 0.0f, 1.0f};
	Color Color::blue = Color{0.0f, 0.0f, 1.0f, 1.0f};
	Color Color::green = Color{0.0f, 1.0f, 0.0f, 1.0f};
	Color Color::black = Color{0.0f, 0.0f, 0.0f, 1.0f};
	Color Color::transparent = Color{0.0f, 0.0f, 0.0f, 0.0f};

} //ASEngine
