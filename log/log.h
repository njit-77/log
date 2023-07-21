#pragma once

#define LOG_PATH  "./log/"


#include <direct.h>
#include <sstream>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>


#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"

/*
*	1、2022.01.18 更新spdlog版本，由1.5.0->1.9.2
*	2、2023.01.19 更新spdlog版本，由1.9.2->1.11.0
*	3、2023.07.21 更新spdlog版本，由1.11.0->1.12.0
*/

class Log
{
public:

	static Log& GetInstance()
	{
		static Log m_instance;
		return m_instance;
	}

	void InitLog(const char* file_name = "log")
	{
		std::string full_file_name;
		full_file_name.append(LOG_PATH).append(file_name).append(".log");

		auto logger_name = generate_hex(16);
		logger = spdlog::daily_logger_mt(logger_name, full_file_name, 0, 0);

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

	Log(const Log&) = delete;

	Log& operator=(const Log&) = delete;

private:
	std::shared_ptr<spdlog::logger> logger;
};
