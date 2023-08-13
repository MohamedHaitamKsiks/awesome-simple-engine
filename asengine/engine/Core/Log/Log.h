
#ifndef ASENGINE_LOG_H
#define ASENGINE_LOG_H

#include<sstream>
#include<string>

namespace ASEngine {

	class Debug {
	public:
		// log args... to console
		template<typename T, typename... types>
		static void Log(T firstValue,types... args)
		{
			std::stringstream ss;
			Debug::PushToStringStream(ss, firstValue, args...);

			Debug::Log(ss.str());
		};

		// log message to console
		static void Log(const std::string &message);

	private:
		// push args to string stream
		template <typename T, typename... types>
		static void PushToStringStream(std::stringstream& ss, T firstValue, types... args)
		{
			ss << firstValue << " ";

			if constexpr(sizeof...(args) > 0)
				PushToStringStream(ss, args...);
		};
	};

} // ASEngine

#endif //ASENGINE_LOG_H
