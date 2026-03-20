#pragma once

#define LOG_PATH  "./log/"


#include <direct.h>
#include <sstream>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>

class Log
{
public:

	static Log& GetInstance()
	{
		static Log m_instance;
		return m_instance;
	}

	void InitLog(const char* file_name = "log", bool console = false)
	{
		std::string full_file_name;
		full_file_name.append(LOG_PATH).append(file_name).append(".log");

		if (console)
		{
			auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(full_file_name, 0, 0);
			auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

			logger = std::make_shared<spdlog::logger>("multi_sink",
				spdlog::sinks_init_list{ daily_sink, console_sink });
		}
		else
		{
			auto logger_name = generate_hex(16);
			logger = spdlog::daily_logger_mt(logger_name, full_file_name, 0, 0);
		}

		logger->set_pattern("%Y-%m-%d %H:%M:%S.%e	[ThreadId:%5t]	[Loglevel:%8l]	%v");
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::err);
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

	Log(const Log&) = delete;

	Log& operator=(const Log&) = delete;

	Log()
	{
		if (_access(LOG_PATH, 0) != 0)
		{
			_mkdir(LOG_PATH);
		}
	}

	~Log()
	{
		spdlog::shutdown();
	}

	unsigned char random_char()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 255);
		return static_cast<unsigned char>(dis(gen));
	}

	std::string generate_hex(const unsigned int len)
	{
		std::stringstream ss;
		for (auto i = 0; i < len; i++)
		{
			auto rc = random_char();
			std::stringstream hexstream;
			hexstream << std::hex << int(rc);
			auto hex = hexstream.str();
			ss << (hex.length() < 2 ? '0' + hex : hex);
		}
		return ss.str();
	}

private:
	std::shared_ptr<spdlog::logger> logger;
};
