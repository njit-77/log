// Testlog.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstdarg>

#pragma comment(lib, "log.lib")

#ifdef LOG_EXPORTS
#define LOG_API __declspec(dllexport)
#else
#define LOG_API __declspec(dllimport)
#endif
LOG_API void LogTrace(const char* m, ...);


int main()
{
	LogTrace("Today %d-%d-%d is the day.", 2019, 11, 30);
	LogTrace("今天 %d-%d-%d 天气不错.", 2019, 11, 30);
	LogTrace("Today[今天] 2019-11-30 天气不错.");
}

