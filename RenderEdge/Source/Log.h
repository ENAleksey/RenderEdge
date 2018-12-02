#pragma once

#include <fstream>
#include <iomanip>
#include <sstream>

#define LOG(LEVEL) LOG_##LEVEL()
#define LOG_INFO() Log::Message(Log::ELevel::Info)
#define LOG_ERROR() Log::Message(Log::ELevel::Error)
#define LOG_WARNING() Log::Message(Log::ELevel::Warning)
#define LOG_DEBUG() Log::Message(Log::ELevel::Debug)
#define LOG_SCREEN() ScreenLog::Message()

namespace ScreenLog
{
	extern std::ostringstream stream;

	struct Message
	{
		Message();
		~Message();

		template <typename T>
		inline Message &operator<<(const T &value)
		{
			stream << value;
			return *this;
		}

		inline Message &operator<<(const char *message)
		{
			stream << message;
			return *this;
		}
	};

	void Clear();
}

namespace Log
{
	enum class ELevel
	{
		Error = 1,
		Warning = 2,
		Info = 3,
		Debug = 4,
	};

	extern bool bDebug;
	extern std::ofstream stream;
	
	struct Message
	{
		bool bInvalidMessage;

		Message(ELevel level);
		~Message();

		template <typename T>
		inline Message &operator<<(const T &value)
		{
			if (bInvalidMessage)
				return *this;

			stream << value;

			return *this;
		}

		inline Message &operator<<(const char *message)
		{
			if (bInvalidMessage)
				return *this;

			stream << message;

			return *this;
		}
	};

	bool Open(const std::string& path);
}