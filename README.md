# log

```apl
基于开源库spdlog(1.13.0)简单封装，方便多工程(c++/c#)统一日志接口。
```



### 使用

```apl
* 头文件

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
LOG_API void SetLogLevel(int level);
LOG_API void SetLogFileName(const char* file_name, HMODULE hModule);
```

