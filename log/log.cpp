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

LOG_API void SetLogLevel(int level)
{
	if (level < spdlog::level::trace) level = spdlog::level::trace;
	if (level > spdlog::level::off) level = spdlog::level::off;
	spdlog::set_level((spdlog::level::level_enum)level);
}

namespace Hardware_Information
{
	/// OS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") 
#pragma warning(disable: 4996)

/// CPU
#include <intrin.h>

/// Network
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")

/// GPU
#include <vector>
#include <DXGI.h>  
#pragma comment(lib, "DXGI.lib")

#pragma comment(lib, "version")

	template<typename ... Args>
	std::string format_string(const std::string &format, Args ... args)
	{
		auto size_buf = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		std::unique_ptr<char[]> buf(new(std::nothrow) char[size_buf]);

		if (!buf)
			return std::string("");

		std::snprintf(buf.get(), size_buf, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size_buf - 1);
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

	void getOSInfo()
	{
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

		TCHAR szComputerName[SHRT_MAX];
		DWORD dwNameLen = SHRT_MAX;
		GetComputerName(szComputerName, &dwNameLen);

		TCHAR szUserName[SHRT_MAX];
		dwNameLen = SHRT_MAX;
		GetUserName(szUserName, &dwNameLen);

		std::string cpu_info = format_string("[OS]操作系统: %s, 版本：%d.%d, 计算机名：%s，用户名：%s.",
			os_name.c_str(),
			osver.dwMajorVersion,
			osver.dwMinorVersion,
			TCHAR2STRING(szComputerName).c_str(),
			TCHAR2STRING(szUserName).c_str());
		LogTrace(cpu_info.c_str());
	}

	void getCPUInfo()
	{
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

		std::string cpu_info = format_string("[CPU]CPU型号：%s%s%s.",
			cpu_manufacture,
			cpu_type,
			cpu_freq);
		LogTrace(cpu_info.c_str());
	}

	void getMemoryInfo()
	{
		MEMORYSTATUSEX statusex;
		statusex.dwLength = sizeof(statusex);
		GlobalMemoryStatusEx(&statusex);

		std::string memory_info = format_string("[Memory]内存共%.2fGB，当前可用%.2fGB.",
			statusex.ullTotalPhys / std::pow(1024, 3),
			statusex.ullAvailPhys / std::pow(1024, 3));
		LogTrace(memory_info.c_str());
	}

	void getNetworkInfo()
	{
		unsigned long adapter_size = sizeof(IP_ADAPTER_INFO);
		PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
		if (pAdapterInfo != nullptr)
		{
			int ret = GetAdaptersInfo(pAdapterInfo, &adapter_size);
			if (ret == NO_ERROR)
			{
				int NetCard = 0;
				for (PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter != nullptr; pAdapter = pAdapterInfo->Next)
				{
					/// 确保是以太网
					if (pAdapter->Type != MIB_IF_TYPE_ETHERNET
						|| pAdapter->Type == 71
						|| strstr(pAdapter->Description, "Bluetooth") > 0)
					{
						continue;
					}

					/// 确保MAC地址长度为XX-XX-XX-XX-XX-XX
					if (pAdapter->AddressLength != 6)
					{
						continue;
					}

					PIP_ADDR_STRING pIpAddr = &(pAdapter->IpAddressList);
					char local_mac[128] = { 0 };
					int char_index = 0;
					for (int i = 0; i < pAdapter->AddressLength; i++)
					{
						char temp_str[10] = { 0 };
						sprintf(temp_str, "%02X-", pAdapter->Address[i]);
						strcpy(local_mac + char_index, temp_str);
						char_index += 3;
					}
					local_mac[17] = '\0'; /// remove tail '-'

					NetCard++;
					std::string network_info = format_string("[Network]网卡%d，网卡描述：%s.\n网卡序列号：%s.\nIP：%s.\n子网掩码：%s.\nMAC：%s.",
						NetCard,
						pAdapter->Description,
						pAdapter->AdapterName,
						pIpAddr->IpAddress.String,
						pIpAddr->IpMask.String,
						local_mac);
					LogTrace(network_info.c_str());
				}
			}
		}
	}

	std::string WStringToString(const std::wstring &wstr)
	{
		std::string str(wstr.length(), ' ');
		std::copy(wstr.begin(), wstr.end(), str.begin());
		return str;
	}

	void getGPUInfo()
	{
		/// 参数定义  
		IDXGIFactory * pFactory;
		IDXGIAdapter * pAdapter;
		std::vector <IDXGIAdapter*> vAdapters;
		int iAdapterNum = 0;

		/// 创建一个DXGI工厂  
		HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));

		if (FAILED(hr))
			return;

		/// 枚举适配器  
		while (pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND)
		{
			vAdapters.push_back(pAdapter);
			++iAdapterNum;
		}

		/// 输出显卡信息  
		for (size_t i = 0; i < vAdapters.size(); i++)
		{
			/// 获取信息  
			DXGI_ADAPTER_DESC adapterDesc;
			vAdapters[i]->GetDesc(&adapterDesc);
			std::wstring aa(adapterDesc.Description);
			std::string bb = WStringToString(aa);

			std::string videocard_info = format_string("[VideoCard]显卡%d，专用视频内存：%.2fMB，系统视频内存：%.2fMB，设备描述：%s.",
				i + 1,
				adapterDesc.DedicatedVideoMemory / std::pow(1024, 2),
				adapterDesc.DedicatedSystemMemory / std::pow(1024, 2),
				bb.c_str());

			/// 输出设备  
			IDXGIOutput * pOutput;
			std::vector<IDXGIOutput*> vOutputs;
			/// 输出设备数量  
			int iOutputNum = 0;
			while (vAdapters[i]->EnumOutputs(iOutputNum, &pOutput) != DXGI_ERROR_NOT_FOUND)
			{
				vOutputs.push_back(pOutput);
				iOutputNum++;
			}

			for (size_t n = 0; n < vOutputs.size(); n++)
			{
				/// 获取显示设备信息  
				DXGI_OUTPUT_DESC outputDesc;
				vOutputs[n]->GetDesc(&outputDesc);

				/// 获取设备支持  
				UINT uModeNum = 0;
				DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
				UINT flags = DXGI_ENUM_MODES_INTERLACED;

				vOutputs[n]->GetDisplayModeList(format, flags, &uModeNum, 0);
				DXGI_MODE_DESC * pModeDescs = new DXGI_MODE_DESC[uModeNum];
				vOutputs[n]->GetDisplayModeList(format, flags, &uModeNum, pModeDescs);

				videocard_info.append(format_string("\n显示器%d分辨率：%d * %d.", n + 1,
					outputDesc.DesktopCoordinates.right - outputDesc.DesktopCoordinates.left,
					outputDesc.DesktopCoordinates.bottom - outputDesc.DesktopCoordinates.top));
			}
			vOutputs.clear();

			LogTrace(videocard_info.c_str());
		}
		vAdapters.clear();
	}

	std::string execCmd(const char *cmd)
	{
		char buffer[128] = { 0 };
		std::string result;
		FILE *pipe = _popen(cmd, "r");
		if (!pipe)
			throw std::runtime_error("_popen() failed!");
		while (!feof(pipe))
		{
			if (fgets(buffer, 128, pipe) != NULL)
			{
				std::string serial = buffer;
				if (serial.find("SerialNumber") == -1)
				{
					while (serial.length() > 0 && (serial.back() == '\r' || serial.back() == '\n' || serial.back() == ' '))
					{
						serial.erase(serial.end() - 1);
					}
					if (serial.length() > 0)
					{
						result.append(serial).append(",");
					}
				}
			}
		}
		_pclose(pipe);

		if (result.length() > 1)
		{
			result.erase(result.end() - 1);
		}
		return result;
	}

	void getHardDiskInfo()
	{
		std::string hd_seiral = execCmd("wmic path win32_physicalmedia get SerialNumber");

		std::string harddisk_info = format_string("[HardDisk]HardDisk Serial Number: %s.",
			hd_seiral.c_str());
		LogTrace(harddisk_info.c_str());
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
			/// 判断系统能否检索到指定文件的版本信息
			DWORD dwDataSize = ::GetFileVersionInfoSizeA((LPCSTR)szModuleName.c_str(), &dwHandle);
			if (dwDataSize == 0)
				break;

			m_lpVersionData = new (std::nothrow) BYTE[dwDataSize];/// 分配缓冲区
			if (NULL == m_lpVersionData)
				break;

			/// 检索信息
			if (!::GetFileVersionInfoA((LPCSTR)szModuleName.c_str(), dwHandle, dwDataSize,
				(void*)m_lpVersionData))
				break;

			UINT nQuerySize;
			DWORD* pTransTable;
			/// 设置语言
			if (!::VerQueryValueA(m_lpVersionData, "\\VarFileInfo\\Translation", (void **)&pTransTable, &nQuerySize))
				break;

			m_dwLangCharset = MAKELONG(HIWORD(pTransTable[0]), LOWORD(pTransTable[0]));
			if (m_lpVersionData == NULL)
				break;

			tmpstr = new (std::nothrow) CHAR[128];/// 分配缓冲区
			if (NULL == tmpstr)
				break;
			sprintf_s(tmpstr, 128, "\\StringFileInfo\\%08lx\\%s", m_dwLangCharset, ValueName.c_str());
			LPVOID lpData;

			/// 调用此函数查询前需要先依次调用函数GetFileVersionInfoSize和GetFileVersionInfo
			if (::VerQueryValueA((void *)m_lpVersionData, tmpstr, &lpData, &nQuerySize))
				RetStr = (char*)lpData;

			bSuccess = TRUE;
		} while (FALSE);

		/// 销毁缓冲区
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

	void getFileInfo(HMODULE hModule)
	{
		TCHAR szBuff[0xff] = { 0 };
		GetModuleFileName(hModule, szBuff, MAX_PATH);

		std::string module_name = TCHAR2STRING(szBuff);

		/// 获取文件说明
		std::string file_description;
		QueryValue("FileDescription", module_name, file_description);
		LogTrace("[FileInfo]FileDescription：%s.",
			file_description.c_str());

		/// 获取文件版本
		std::string file_version;
		QueryValue("FileVersion", module_name, file_version);
		LogTrace("[FileInfo]FileVersion：%s.",
			file_version.c_str());

		/// 获取产品名称
		std::string product_name;
		QueryValue("ProductName", module_name, product_name);
		LogTrace("[FileInfo]ProductName：%s.",
			product_name.c_str());
	}
}

void LogOutputSystemMessage(HMODULE hModule)
{
	LogTrace("\n\n\n");
	LogTrace("******************************************");

	Hardware_Information::getOSInfo();

	Hardware_Information::getCPUInfo();

	Hardware_Information::getMemoryInfo();

	Hardware_Information::getNetworkInfo();

	Hardware_Information::getGPUInfo();

	Hardware_Information::getHardDiskInfo();

	Hardware_Information::getFileInfo(hModule);
}

LOG_API void SetLogFileName(const char* file_name, HMODULE hModule)
{
	Log::GetInstance().InitLog(file_name);
	LogOutputSystemMessage(hModule);
}
