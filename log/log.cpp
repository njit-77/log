#include "log.h"

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") 

#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma warning(disable: 4996)

#pragma comment(lib, "version")

#ifdef LOG_EXPORTS
#define LOG_API __declspec(dllexport)
#else
#define LOG_API __declspec(dllimport)
#endif

#define LOGBUF 1024
static const int kMaxInfoBuffer = 256;
#define GBYTES  1073741824  
#define MBYTES  1048576  
#define KBYTES  1024  
#define DKBYTES 1024.0 


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

LOG_API void SetLogLevel(int level)
{
	if (level < spdlog::level::trace) level = spdlog::level::trace;
	if (level > spdlog::level::off) level = spdlog::level::off;
	spdlog::set_level((spdlog::level::level_enum)level);
}

std::string execCmd(const char *cmd)
{
	char buffer[128] = { 0 };
	std::string result;
	FILE *pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("_popen() failed!");
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	_pclose(pipe);

	return result;
}

LOG_API void SetLogFileName(const char* file_name)
{
	Log::GetInstance().InitLog(file_name);
}

bool QueryValue(const std::string& ValueName, const std::string& szModuleName, std::string& RetStr)
{
	bool bSuccess = FALSE;
	BYTE*  m_lpVersionData = NULL;
	DWORD   m_dwLangCharset = 0;
	CHAR *tmpstr = NULL;

	do
	{
		if (!ValueName.size() || !szModuleName.size())
			break;

		DWORD dwHandle;
		// 判断系统能否检索到指定文件的版本信息
		DWORD dwDataSize = ::GetFileVersionInfoSizeA((LPCSTR)szModuleName.c_str(), &dwHandle);
		if (dwDataSize == 0)
			break;

		m_lpVersionData = new (std::nothrow) BYTE[dwDataSize];// 分配缓冲区
		if (NULL == m_lpVersionData)
			break;

		// 检索信息
		if (!::GetFileVersionInfoA((LPCSTR)szModuleName.c_str(), dwHandle, dwDataSize,
			(void*)m_lpVersionData))
			break;

		UINT nQuerySize;
		DWORD* pTransTable;
		// 设置语言
		if (!::VerQueryValueA(m_lpVersionData, "\\VarFileInfo\\Translation", (void **)&pTransTable, &nQuerySize))
			break;

		m_dwLangCharset = MAKELONG(HIWORD(pTransTable[0]), LOWORD(pTransTable[0]));
		if (m_lpVersionData == NULL)
			break;

		tmpstr = new (std::nothrow) CHAR[128];// 分配缓冲区
		if (NULL == tmpstr)
			break;
		sprintf_s(tmpstr, 128, "\\StringFileInfo\\%08lx\\%s", m_dwLangCharset, ValueName.c_str());
		LPVOID lpData;

		// 调用此函数查询前需要先依次调用函数GetFileVersionInfoSize和GetFileVersionInfo
		if (::VerQueryValueA((void *)m_lpVersionData, tmpstr, &lpData, &nQuerySize))
			RetStr = (char*)lpData;

		bSuccess = TRUE;
	} while (FALSE);

	// 销毁缓冲区
	if (m_lpVersionData)
	{
		delete[] m_lpVersionData;
		m_lpVersionData = NULL;
	}
	if (tmpstr)
	{
		delete[] tmpstr;
		tmpstr = NULL;
	}

	return bSuccess;
}

HMODULE GetSelfModuleHandle()
{
	MEMORY_BASIC_INFORMATION mbi;
	return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
}

std::string TCHAR2STRING(TCHAR* str)
{
	std::string strstr;
	int iLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	char* chRtn = new char[iLen * sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, str, -1, chRtn, iLen, NULL, NULL);
	strstr = chRtn;
	return strstr;
}

LOG_API void LogOutputSystemMessage()
{
	/// OS Information
	{
		LogTrace("*********************OS Information*********************");
		/// get os name according to version number
		OSVERSIONINFO osver = { sizeof(OSVERSIONINFO) };
		GetVersionEx(&osver);
		std::string os_name;
		if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)
			os_name = "Windows 2000";
		else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)
			os_name = "Windows XP";
		else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)
			os_name = "Windows 2003";
		else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)
			os_name = "windows vista";
		else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)
			os_name = "windows 7";
		else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2)
			os_name = "windows 10";

		LogTrace("OS name: %s", os_name.c_str());
		LogTrace("OS version: %d.%d", osver.dwMajorVersion, osver.dwMinorVersion);

		WSADATA WSAData;
		if (!WSAStartup(MAKEWORD(2, 0), &WSAData))
		{
			char hostName[256];
			if (!gethostname(hostName, sizeof(hostName)))
			{
				LogTrace("主机名: %s", hostName);
			}
		}
		WSACleanup();
	}

	/// CPU Infomation
	{
		LogTrace("*********************CPU Infomation*********************");

		int cpuInfo[4] = { -1 };
		char cpu_manufacture[32] = { 0 };
		char cpu_type[32] = { 0 };
		char cpu_freq[32] = { 0 };

		__cpuid(cpuInfo, 0x80000002);
		memcpy(cpu_manufacture, cpuInfo, sizeof(cpuInfo));

		__cpuid(cpuInfo, 0x80000003);
		memcpy(cpu_type, cpuInfo, sizeof(cpuInfo));

		__cpuid(cpuInfo, 0x80000004);
		memcpy(cpu_freq, cpuInfo, sizeof(cpuInfo));

		LogTrace("CPU manufacture: %s", cpu_manufacture);
		LogTrace("CPU type: %s", cpu_type);
		LogTrace("CPU main frequency: %s", cpu_freq);
	}

	/// Memory Information
	{
		LogTrace("*********************Memory Information*********************");

		std::string memory_info;
		MEMORYSTATUSEX statusex;
		statusex.dwLength = sizeof(statusex);
		if (GlobalMemoryStatusEx(&statusex))
		{
			unsigned long long total = 0, remain_total = 0, avl = 0, remain_avl = 0;
			double decimal_total = 0, decimal_avl = 0;
			remain_total = statusex.ullTotalPhys % GBYTES;
			total = statusex.ullTotalPhys / GBYTES;
			avl = statusex.ullAvailPhys / GBYTES;
			remain_avl = statusex.ullAvailPhys % GBYTES;
			if (remain_total > 0)
				decimal_total = (remain_total / MBYTES) / DKBYTES;
			if (remain_avl > 0)
				decimal_avl = (remain_avl / MBYTES) / DKBYTES;

			decimal_total += (double)total;
			decimal_avl += (double)avl;
			char buffer[kMaxInfoBuffer];
			sprintf_s(buffer, kMaxInfoBuffer, "total %.2f GB (%.2f GB available)", decimal_total, decimal_avl);
			memory_info.append(buffer);
		}
		LogTrace("%s", memory_info.c_str());
	}

	/// HardDisk Information
	{
		LogTrace("*********************HardDisk Information*********************");

		std::string hd_seiral = execCmd("wmic path win32_physicalmedia get SerialNumber");
		LogTrace("HardDisk Serial Number: \n%s", hd_seiral.c_str());
	}

	/// NetWork Information
	{
		LogTrace("*********************NetWork Information*********************");

		// PIP_ADAPTER_INFO struct contains network information
		PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
		unsigned long adapter_size = sizeof(IP_ADAPTER_INFO);
		int ret = GetAdaptersInfo(pIpAdapterInfo, &adapter_size);

		if (ret == ERROR_BUFFER_OVERFLOW)
		{
			// overflow, use the output size to recreate the handler
			delete pIpAdapterInfo;
			pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[adapter_size];
			ret = GetAdaptersInfo(pIpAdapterInfo, &adapter_size);
		}

		if (ret == ERROR_SUCCESS)
		{
			int card_index = 0;

			// may have many cards, it saved in linklist
			while (pIpAdapterInfo)
			{
				LogTrace("-------NetworkCard %d-------", card_index);
				LogTrace("Network Card Name: %s", pIpAdapterInfo->AdapterName);
				LogTrace("Network Card Description: %s", pIpAdapterInfo->Description);

				// get IP, one card may have many IPs
				PIP_ADDR_STRING pIpAddr = &(pIpAdapterInfo->IpAddressList);
				while (pIpAddr)
				{
					char local_ip[128] = { 0 };
					strcpy(local_ip, pIpAddr->IpAddress.String);
					LogTrace("Local IP: %s", local_ip);

					pIpAddr = pIpAddr->Next;
				}

				char local_mac[128] = { 0 };
				int char_index = 0;
				for (int i = 0; i < static_cast<int>(pIpAdapterInfo->AddressLength); i++)
				{
					char temp_str[10] = { 0 };
					sprintf(temp_str, "%02X-", pIpAdapterInfo->Address[i]); // X for uppercase, x for lowercase
					strcpy(local_mac + char_index, temp_str);
					char_index += 3;
				}
				local_mac[17] = '\0'; // remove tail '-'

				LogTrace("Local Mac: %s", local_mac);

				// here just need the first card info
				break;
			}
		}

		if (pIpAdapterInfo)
			delete pIpAdapterInfo;
	}

	/// FileAttribute Information
	{
		LogTrace("*********************FileAttribute Information*********************");

		TCHAR szBuff[0xff] = { 0 };
		GetModuleFileName(GetSelfModuleHandle(), szBuff, MAX_PATH);
		std::string module_name = TCHAR2STRING(szBuff);

		std::string value;
		/// 获取文件说明
		QueryValue("FileDescription", module_name, value);
		LogTrace("FileDescription:%s.", value.c_str());

		/// 获取文件版本
		QueryValue("FileVersion", module_name, value);
		LogTrace("FileVersion:%s.", value.c_str());

		///// 获取内部名称
		//QueryValue("InternalName", module_name, value);
		//LogTrace("InternalName:%s.", value.c_str());

		///// 获取公司名称
		//QueryValue("CompanyName", module_name, value);
		//LogTrace("CompanyName:%s.", value.c_str());

		///// 获取版权
		//QueryValue("LegalCopyright", module_name, value);
		//LogTrace("LegalCopyright:%s.", value.c_str());

		///// 获取原始文件名
		//QueryValue("OriginalFilename", module_name, value);
		//LogTrace("OriginalFilename:%s.", value.c_str());

		///// 获取产品名称
		//QueryValue("ProductName", module_name, value);
		//LogTrace("ProductName:%s.", value.c_str());

		///// 获取产品版本
		//QueryValue("ProductVersion", module_name, value);
		//LogTrace("ProductVersion:%s.", value.c_str());
	}
}