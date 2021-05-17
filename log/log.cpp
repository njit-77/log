#include "log.h"

#ifdef LOG_EXPORTS
#define LOG_API __declspec(dllexport)
#else
#define LOG_API __declspec(dllimport)
#endif

#define LOGBUF 1024

LOG_API void LogTrace(const char* m, ...)
{
	if (Log::GetInstance().GetLogger()->level() <= spdlog::level::trace)
	{
		char strLogBuf[LOGBUF] = { 0 };
		va_list arg_list;
		va_start(arg_list, m);
		vsprintf_s(strLogBuf, m, arg_list);
		Log::GetInstance().GetLogger()->trace(strLogBuf);
		va_end(arg_list);
	}
}

LOG_API void LogDebug(const char* m, ...)
{
	if (Log::GetInstance().GetLogger()->level() <= spdlog::level::debug)
	{
		char strLogBuf[LOGBUF] = { 0 };
		va_list arg_list;
		va_start(arg_list, m);
		vsprintf_s(strLogBuf, m, arg_list);
		Log::GetInstance().GetLogger()->debug(strLogBuf);
		va_end(arg_list);
	}
}

LOG_API void LogInfo(const char* m, ...)
{
	if (Log::GetInstance().GetLogger()->level() <= spdlog::level::info)
	{
		char strLogBuf[LOGBUF] = { 0 };
		va_list arg_list;
		va_start(arg_list, m);
		vsprintf_s(strLogBuf, m, arg_list);
		Log::GetInstance().GetLogger()->info(strLogBuf);
		va_end(arg_list);
	}
}

LOG_API void LogWarn(const char* m, ...)
{
	if (Log::GetInstance().GetLogger()->level() <= spdlog::level::warn)
	{
		char strLogBuf[LOGBUF] = { 0 };
		va_list arg_list;
		va_start(arg_list, m);
		vsprintf_s(strLogBuf, m, arg_list);
		Log::GetInstance().GetLogger()->warn(strLogBuf);
		va_end(arg_list);
	}
}

LOG_API void LogError(const char* m, ...)
{
	if (Log::GetInstance().GetLogger()->level() <= spdlog::level::err)
	{
		char strLogBuf[LOGBUF] = { 0 };
		va_list arg_list;
		va_start(arg_list, m);
		vsprintf_s(strLogBuf, m, arg_list);
		Log::GetInstance().GetLogger()->error(strLogBuf);
		va_end(arg_list);
	}
}

LOG_API void LogCritical(const char* m, ...)
{
	if (Log::GetInstance().GetLogger()->level() <= spdlog::level::critical)
	{
		char strLogBuf[LOGBUF] = { 0 };
		va_list arg_list;
		va_start(arg_list, m);
		vsprintf_s(strLogBuf, m, arg_list);
		Log::GetInstance().GetLogger()->critical(strLogBuf);
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