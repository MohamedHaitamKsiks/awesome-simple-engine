//
// Created by ksiks_wa3r on 5/30/23.
//

#ifndef ANDROIDSIMPLEENGINE_LOG_H
#define ANDROIDSIMPLEENGINE_LOG_H

#include<string>

namespace ASEngine {

	class Log {
	public:
		static void out(const std::string& message);
		static void out(int value);
	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_LOG_H
