
#ifndef ASENGINE_LOG_H
#define ASENGINE_LOG_H

#include<sstream>
#include<string>

namespace ASEngine {

	class Log {
	public:
		// log args... to console
		template<typename T, typename... types>
		static void out(T firstValue,types... args)
		{
			std::stringstream ss;
			Log::pushToStringStream(ss, firstValue, args...);

			Log::out(ss.str());
		};

		// log message to console
		static void out(const std::string &message);

	private:
		// push args to string stream
		template <typename T, typename... types>
		static void pushToStringStream(std::stringstream& ss, T firstValue, types... args)
		{
			ss << firstValue;

			if constexpr(sizeof...(args) > 0)
				pushToStringStream(ss, args...);
		};
	};

} // ASEngine

#endif //ASENGINE_LOG_H
