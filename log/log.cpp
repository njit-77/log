#include "log.h"


LOG_API void LogTrace(const char* m, ...)
{
	if (Log::GetInstance().GetLogger()->level() >= spdlog::level::trace)
	{
		char strLogBuf[1024] = { 0 };
		va_list arg_list;
		va_start(arg_list, m);
		vsprintf_s(strLogBuf, m, arg_list);
		Log::GetInstance().GetLogger()->trace(strLogBuf);
		va_end(arg_list);
	}
}

LOG_API void SetLogTrace()
{
	spdlog::set_level(spdlog::level::trace);
}

LOG_API void SetLogDebug()
{
	spdlog::set_level(spdlog::level::debug);
}

LOG_API void SetLogInfo()
{
	spdlog::set_level(spdlog::level::info);
}

LOG_API void SetLogWarn()
{
	spdlog::set_level(spdlog::level::warn);
}

LOG_API void SetLogError()
{
	spdlog::set_level(spdlog::level::err);
}

LOG_API void SetLogCritical()
{
	spdlog::set_level(spdlog::level::critical);
}

LOG_API void SetLogOff()
{
	spdlog::set_level(spdlog::level::off);
}