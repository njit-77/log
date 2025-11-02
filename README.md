# log

This is a simple encapsulation based on the open-source library [spdlog](https://github.com/gabime/spdlog) (1.16.0), which facilitates a unified logging interface for multiple projects (C++/C#).

基于开源库[spdlog](https://github.com/gabime/spdlog)(1.16.0)简单封装，方便多工程(c++/c#)统一日志接口。



#### Development  Tools / 开发工具

```apl
Visual Studio 2022 Community
```



#### Target Framework / 目标框架

```apl
window skd 10.0.26100.0
```

#### 

### Usage samples  / 用例

```c++
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
LOG_API void SetLogFileName(const char* file_name, HMODULE hModule);


int main()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	SetLogFileName("Testlog", NULL);

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
```

