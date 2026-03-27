#include <iostream>

#include "log_export.h"
#pragma comment(lib, "log.lib")


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetLogFileName("Testlog", GetModuleHandle(TEXT("log.dll")), true);

	SYSTEMTIME sys;
	GetLocalTime(&sys);

	for (int i = 0; i < level_enum::off; i++)
	{
		SetLogLevel(i);
		LogTrace("This is a Trace Log, Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
		LogDebug("This is a Debug Log, Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
		LogInfo("This is a Info Log, Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
		LogWarn("This is a Warn Log, Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
		LogError("This is a Error Log, Today[%d-%d-%d] is the day, 天气不错.", sys.wYear, sys.wMonth, sys.wDay);
		LogCritical("This is a Critical Log, Today[%d-%d-%d] is the day, 天气不错.\n", sys.wYear, sys.wMonth, sys.wDay);
	}
	system("pause");
}
