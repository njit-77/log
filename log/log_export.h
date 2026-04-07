#pragma once

#include<Windows.h>

#ifdef LOG_EXPORTS
#define LOG_API __declspec(dllexport) 
#else
#define LOG_API __declspec(dllimport)
#endif


LOG_API void __cdecl SetLogFileName(const char* log_name, HMODULE module, bool console);

enum level_enum
{
	trace = 0,
	debug = 1,
	info = 2,
	warn = 3,
	err = 4,
	critical = 5,
	off = 6,
};
LOG_API void __cdecl SetLogLevel(int level);

LOG_API void __cdecl LogTrace(const char* format, ...);
LOG_API void __cdecl LogDebug(const char* format, ...);
LOG_API void __cdecl LogInfo(const char* format, ...);
LOG_API void __cdecl LogWarn(const char* format, ...);
LOG_API void __cdecl LogError(const char* format, ...);
LOG_API void __cdecl LogCritical(const char* format, ...);
