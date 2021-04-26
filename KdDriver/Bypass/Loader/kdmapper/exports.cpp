#include "kdmapper.hpp"
#include "version.h"
#include "../../Universal/vmprotect.h"
#include "exports.h"
#define EXPORT extern "C" __declspec(dllexport)
//#define GAME_EXE E("EscapeFromTarkov.exe")

void DebugWait(int seconds)
{
	Protect();
	printf(E("Waiting... "));
	for (int i = 1; i <= seconds; i++)
	{
		Sleep(1000);
		printf("%i ", i);
	}
	printf("\n");
	ProtectEnd();
}

__forceinline int FakeMapDriver()
{
	Protect();
	HANDLE iqvw64e_device_handle = intel_driver::Load();

	if (!iqvw64e_device_handle || iqvw64e_device_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << E("Failed To Load Vulnerable Driver") << std::endl;
		return -1;
	}

	if (!kdmapper::MapDriver(iqvw64e_device_handle))
	{
		std::cout << E("Failed To Map ") << std::endl;
		intel_driver::Unload(iqvw64e_device_handle);
		return -1;
	}

	intel_driver::Unload(iqvw64e_device_handle);
	std::cout << E("Success") << std::endl;
	DebugWait(2);
	ProtectEnd();
	return 0;
}

__forceinline int dll_MapDriver()
{
	Protect();
	//AllocConsole();
	//freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	//freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	//ShowWindow(GetConsoleWindow(), SW_SHOW);
	int status = FakeMapDriver();

	//Sleep(3000);
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	ProtectEnd();
	return status;
}

int fakemain()
{
	Protect();

	printf(E("Checking version...\n"));
	auto version = GetRealOSVersion();
	printf("Build: %lu Major: %lu Minor: %lu\n", version.dwBuildNumber, version.dwMajorVersion, version.dwMinorVersion);
	dll_MapDriver();

	return 0;

	ProtectEnd();
}

int kdmappermain() 
{
	Protect();
	fakemain();
	ProtectEnd();
	return 0;
}
