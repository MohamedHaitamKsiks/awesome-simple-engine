
#ifndef ASENGINE_DEBUG_H
#define ASENGINE_DEBUG_H

#include<sstream>
#include<string>

namespace ASEngine {

	class Debug
	{
	public:
		// set color types
		enum TextColor
		{
			RED_FG = 31,
			REG_BG = 41,

			GREEN_FG = 32,
			GREEN_BG = 42,

			BLUE_FG = 34,
			BLUE_BG = 44,

			BLACK_FG = 30,
			BLACK_BG = 40,

			WHITE_FG = 37,
			WHITE_BG = 47,

		};

		// colorize log arguments
		template <typename T, typename... types>
		static std::string Colorized(TextColor color, T firstValue, types... args)
		{
			std::stringstream ss;
			Debug::PushToStringStream(ss, firstValue, args...);

			return Colorized(color, ss.str());
		};

		// return colorized text (to be printed by Debug::Log only)
		static std::string Colorized(TextColor color, const std::string& str);
		
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

		// log error message
		template<typename T, typename... types>
		static void Error(T firstValue,types... args)
		{
			Log(Colorized(TextColor::RED_FG, firstValue, args...));
		};

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
