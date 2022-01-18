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
LOG_API void SetLogTrace();
LOG_API void SetLogDebug();
LOG_API void SetLogInfo();
LOG_API void SetLogWarn();
LOG_API void SetLogError();
LOG_API void SetLogCritical();
LOG_API void SetLogOff();
LOG_API void LogOutputSystemMessage();

int main()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	SetLogTrace();
	LogOutputSystemMessage();
	LogTrace("[SetLogTrace]This is a Trace Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogDebug("[SetLogTrace]This is a Debug Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogInfo("[SetLogTrace]This is a Info Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogWarn("[SetLogTrace]This is a Warn Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogError("[SetLogTrace]This is a Error Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogCritical("[SetLogTrace]This is a Critical Log.Today[%d-%d-%d] is the day, 天气不错.\n", sys.wYear, sys.wMonth, sys.wDay);

	SetLogDebug();
	LogTrace("[SetLogDebug]This is a Trace Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogDebug("[SetLogDebug]This is a Debug Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogInfo("[SetLogDebug]This is a Info Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogWarn("[SetLogDebug]This is a Warn Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogError("[SetLogDebug]This is a Error Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogCritical("[SetLogDebug]This is a Critical Log.Today[%d-%d-%d] is the day, 天气不错.\n", sys.wYear, sys.wMonth, sys.wDay);

	SetLogInfo();
	LogTrace("[SetLogInfo]This is a Trace Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogDebug("[SetLogInfo]This is a Debug Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogInfo("[SetLogInfo]This is a Info Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogWarn("[SetLogInfo]This is a Warn Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogError("[SetLogInfo]This is a Error Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogCritical("[SetLogInfo]This is a Critical Log.Today[%d-%d-%d] is the day, 天气不错.\n", sys.wYear, sys.wMonth, sys.wDay);

	SetLogWarn();
	LogTrace("[SetLogWarn]This is a Trace Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogDebug("[SetLogWarn]This is a Debug Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogInfo("[SetLogWarn]This is a Info Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogWarn("[SetLogWarn]This is a Warn Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogError("[SetLogWarn]This is a Error Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogCritical("[SetLogWarn]This is a Critical Log.Today[%d-%d-%d] is the day, 天气不错.\n", sys.wYear, sys.wMonth, sys.wDay);

	SetLogError();
	LogTrace("[SetLogError]This is a Trace Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogDebug("[SetLogError]This is a Debug Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogInfo("[SetLogError]This is a Info Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogWarn("[SetLogError]This is a Warn Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogError("[SetLogError]This is a Error Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogCritical("[SetLogError]This is a Critical Log.Today[%d-%d-%d] is the day, 天气不错.\n", sys.wYear, sys.wMonth, sys.wDay);

	SetLogCritical();
	LogTrace("[SetLogCritical]This is a Trace Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogDebug("[SetLogCritical]This is a Debug Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogInfo("[SetLogCritical]This is a Info Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogWarn("[SetLogCritical]This is a Warn Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogError("[SetLogCritical]This is a Error Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogCritical("[SetLogCritical]This is a Critical Log.Today[%d-%d-%d] is the day, 天气不错.\n", sys.wYear, sys.wMonth, sys.wDay);

	SetLogOff();
	LogTrace("[SetLogOff]This is a Trace Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogDebug("[SetLogOff]This is a Debug Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogInfo("[SetLogOff]This is a Info Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogWarn("[SetLogOff]This is a Warn Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogError("[SetLogOff]This is a Error Log.Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
	LogCritical("[SetLogOff]This is a Critical Log.Today[%d-%d-%d] is the day, 天气不错.\n", sys.wYear, sys.wMonth, sys.wDay);

	system("pause");
}
