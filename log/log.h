#pragma once

#define LOG_PATH  "./log/"

#include <direct.h>  

#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"


class Log
{
public:

	static Log& GetInstance()
	{
		static Log m_instance;
		return m_instance;
	}

	inline auto GetLogger() { return logger; }

private:

	Log()
	{
		if (_access(LOG_PATH, 0) != 0)
		{
			_mkdir(LOG_PATH);
		}

		logger = spdlog::daily_logger_mt("daily_logger", "log/log.log", 0, 0);

		logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e]	ThreadId:%5t Loglevel:%8l |	%v");

		logger->flush_on(spdlog::level::trace);

		spdlog::set_level(spdlog::level::trace);
	}

	~Log()
	{
		spdlog::shutdown();
	}

	Log(const Log&) = delete;

	Log& operator=(const Log&) = delete;

private:
	std::shared_ptr<spdlog::logger> logger;
};
