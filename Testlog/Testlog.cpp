// Testlog.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>

#pragma comment(lib, "log.lib")

#ifdef LOG_EXPORTS
#define LOG_API __declspec(dllexport)
#else
#define LOG_API __declspec(dllimport)
#endif

LOG_API void LogTrace(const char* m, ...);
LOG_API void LogDebug(const char* m, ...);
LOG_API void LogInfo(const char* m, ...);
LOG_API void LogWarn(const char* m, ...);
LOG_API void LogError(const char* m, ...);
LOG_API void LogCritical(const char* m, ...);
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
LOG_API void SetLogLevel(int level);
LOG_API void SetLogFileName(const char* file_name);
LOG_API void LogOutputSystemMessage();

int main()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	SetLogFileName("Testlog");
	LogOutputSystemMessage();

	for (int i = 0; i < level_enum::off; i++)
	{
		SetLogLevel(i);
		LogTrace("[SetLogTrace]This is a Trace Log, Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
		LogDebug("[SetLogTrace]This is a Debug Log, Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
		LogInfo("[SetLogTrace]This is a Info Log, Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
		LogWarn("[SetLogTrace]This is a Warn Log, Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
		LogError("[SetLogTrace]This is a Error Log, Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
		LogCritical("[SetLogTrace]This is a Critical Log, Today[%d-%d-%d] is the day, 天气不错.\n", sys.wYear, sys.wMonth, sys.wDay);
	}
	system("pause");
}
