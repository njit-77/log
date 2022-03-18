#pragma once

#define LOG_PATH  "./log/"

#include <direct.h>  

#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"

/// 1、2022-01-18 更新spdlog版本，由1.5.0->1.9.2

class Log
{
public:

	static Log& GetInstance()
	{
		static Log m_instance;
		return m_instance;
	}

	bool InitLog(const char* file_name = "log")
	{
		std::string full_file_name;
		full_file_name.append(LOG_PATH).append(file_name).append(".log");

		logger = spdlog::daily_logger_mt("daily_logger", full_file_name, 0, 0);

		logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e]	ThreadId:%5t Loglevel:%8l |	%v");

		logger->flush_on(spdlog::level::trace);
	}

	inline auto GetLogger()
	{
		if (logger == nullptr)
		{
			InitLog();
		}
		return logger;
	}

private:

	Log()
	{
		if (_access(LOG_PATH, 0) != 0)
		{
			_mkdir(LOG_PATH);
		}

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
