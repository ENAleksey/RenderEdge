#include "Log.h"
#include <mutex>
#include <assert.h>
#include <Windows.h>

namespace ScreenLog
{
	std::ostringstream stream;

	Message::Message()
	{

	}

	Message::~Message()
	{
		stream << std::endl;
	}

	void Clear()
	{
		stream.clear();
	}
}

namespace Log
{
	bool bDebug = false;
	std::ofstream stream;
	static std::mutex s_mutex;

	Message::Message(ELevel level)
	{
		bInvalidMessage = (level == ELevel::Debug) && !bDebug;

		if (bInvalidMessage)
			return;

		SYSTEMTIME time;
		GetLocalTime(&time);

		const char level_names[][7] = { "ERROR:", "WARN: ", "INFO: ", "DEBUG:" };

		s_mutex.lock();

		stream << std::right << std::setfill('0')
			<< std::setw(2) << time.wHour << ':'
			<< std::setw(2) << time.wMinute << ':'
			<< std::setw(2) << time.wSecond << ':'
			<< std::setw(3) << time.wMilliseconds << '\t'
			<< level_names[static_cast<unsigned int>(level) - 1] << '\t' << std::left;
	}

	Message::~Message()
	{
		if (bInvalidMessage)
			return;

		stream << std::endl;

		s_mutex.unlock();
	}

	bool Open(const std::string& path)
	{
		stream.open(path, std::ios::out | std::ios::trunc);

		if (!stream.is_open())
		{
			return false;
		}

		stream.setf(std::ios_base::showbase);

		stream.flush();

		return true;
	}
}