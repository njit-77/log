// Testlog.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstdarg>

#pragma comment(lib, "log.lib")
__declspec(dllimport) void LogTrace(const char* m, ...);

template<typename T>
struct item_return
{
	using type = T&&;
};

template<typename T>
inline typename item_return<T>::type convert(T&& arg)
{
	return static_cast<T&&>(arg);
}

template<typename... Args>
std::string fmt(const char* format, Args... args)
{
	char buf[128] = { 0 };
	snprintf(buf, sizeof(buf), format, convert(std::forward<Args>(args))...);
	return buf;
}

int main()
{
	LogTrace("Today %d-%d-%d is the day.", 2019, 11, 30);
	LogTrace("今天 %d-%d-%d 天气不错.", 2019, 11, 30);
	LogTrace("Today[今天] 2019-11-30 天气不错.");
}

