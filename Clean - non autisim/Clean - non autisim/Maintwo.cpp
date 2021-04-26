#include "Maintwo.h"
#include "bypass.h"




#include <random>






/*
*	Player 1 Booleans
*/
bool infiniteHealth = false;
bool infiniteAmmo = false;
bool infinitePoints = false;
bool alwaysInstaKill = false;
bool alwaysCrit = false;
bool jumpHeight = false;
bool p1Speed = false;
bool zombieTP = false;
bool extraZombiesTP = false;
bool tpAllZombies = false;
bool newZombieLocation = false;
bool playerRankXP = false;
bool playerWeaponXP = false;
bool p1WCycle = false;
bool p1LCycle = false;
bool p1TCycle = false;
bool p1WWCycle = false;
bool p1KSCycle = false;
bool p1FUCycle = false;
bool playerName = false;
bool quickStart = false;
bool skipRounds = false;
bool blaznOneShot = false;
/*
*	Player 2 booleans
*/
bool p2infiniteHealth = false;
bool p2infiniteAmmo = false;
bool p2infinitePoints = false;
bool p2alwaysCrit = false;
bool p2jumpHeight = false;
bool p2zombieTP = false;
bool p2playerTP = false;
bool p2newZombieLocation = false;
bool p2WCycle = false;
bool p2LCycle = false;
bool p2TCycle = false;
bool p2WWCycle = false;
bool p2KSCycle = false;
bool p2FUCycle = false;
/*
*	Player 3 booleans
*/
bool p3infiniteHealth = false;
bool p3infiniteAmmo = false;
bool p3infinitePoints = false;
bool p3alwaysCrit = false;
bool p3jumpHeight = false;
bool p3zombieTP = false;
bool p3playerTP = false;
bool p3newZombieLocation = false;
bool p3WCycle = false;
bool p3LCycle = false;
bool p3TCycle = false;
bool p3WWCycle = false;
bool p3KSCycle = false;
bool p3FUCycle = false;
/*
*	Player 4 booleans
*/
bool p4infiniteHealth = false;
bool p4infiniteAmmo = false;
bool p4infinitePoints = false;
bool p4alwaysCrit = false;
bool p4jumpHeight = false;
bool p4zombieTP = false;
bool p4playerTP = false;
bool p4newZombieLocation = false;
bool p4WCycle = false;
bool p4LCycle = false;
bool p4TCycle = false;
bool p4WWCycle = false;
bool p4KSCycle = false;
bool p4FUCycle = false;
/*
*	Extra Goodies booleans
*/
bool restartGame = false;
bool disconnectGame = false;
bool longRevive = false;
bool freezeBox = false;
bool clientKick1 = false;
float xpval = 0.f;

string keyInput;
DWORD oofBoiii;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}


void axeraMenuBody()
{


	Sleep(1000);

	////////////////////////////////////////														////////////////////////////////////////
	////////////////////									Main Program Function										////////////////////
	////////////////////////////////////////														////////////////////////////////////////
	unique_ptr<DriverManager> driver = std::make_unique<DriverManager>("\\\\.\\NTIOLib_MB");

	while (!driver->GetProcessID("BlackOpsColdWar.exe"))
	{
		system("cls");
		cout << "[+] :Launch The Game First" << endl << endl;
		cout << "[+] : Exiting....";
		this_thread::sleep_for(std::chrono::seconds(5));
		system("cls");
		exit(0);
	}

	system("cls");
	this_thread::sleep_for(std::chrono::seconds(1));

	HWND console2 = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console2, &ConsoleRect);
	ShowWindow(console2, FALSE);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Overlay::Loop, nullptr, 0, nullptr);
	uintptr_t address = driver->GetModuleBaseAddr("BlackOpsColdWar.exe");
	uintptr_t processid = driver->GetProcessID("BlackOpsColdWar.exe");
	HWND yesDaddy = FindWindowA(NULL, "Call of Duty®: Black Ops Cold War");
	GetWindowThreadProcessId(yesDaddy, &oofBoiii);
	HANDLE discordOverlay = OpenProcess(PROCESS_ALL_ACCESS, FALSE, oofBoiii);
	uintptr_t playerBase = address + 0x10A4EE78;
	uintptr_t zombieBase = 0x68;
	uintptr_t botListBase = playerBase + 0x68;
	uintptr_t playerPedBase = playerBase + 0x8;
	uintptr_t jumpHeightBase = address + 0x10B45BA8;
	uintptr_t zombieBotListBase = botListBase + 0x8;
	uintptr_t cmdBufferBase = 0x122B5EE0;
	uintptr_t CMDBB_Exec = -0x1B;
	uintptr_t nextZombieBot = 0x8;
	uintptr_t rankXP = 0x10A76E98;
	uintptr_t weaponXP = 0x108674B0;
	uintptr_t rankOffset = 0x28;
	uintptr_t rankOffset2 = 0x20;
	uintptr_t weaponOffset = 0x30;
	uintptr_t rankValue = 1000.f;
	uintptr_t playerKills = 0x5D38;
	uintptr_t playerNameOffset = 0x5C0A;
	uintptr_t playerName = 0x5C0A;
	uintptr_t godMode = 0xE67;
	uintptr_t points = 0x5D14;
	uintptr_t runSpeed = 0x5C60;
	uintptr_t playerArray = 0xB940; //0x37860
	uintptr_t zombieCritAddr = 0x10D6;
	uintptr_t zombieHealth = 0x398;
	uintptr_t zombieMaxHealth = 0x39C;
	uintptr_t setWeapon = 0xB0;
	uintptr_t ammo = 0x13D4;
	uintptr_t ammo1 = 0x13D4 + 1 * 0x4;
	uintptr_t ammo2 = 0x13D4 + 2 * 0x4;
	uintptr_t ammo3 = 0x13D4 + 3 * 0x4;
	uintptr_t ammo4 = 0x13D4 + 4 * 0x4;
	uintptr_t ammo5 = 0x13D4 + 5 * 0x4;
	uintptr_t ammo6 = 0x13D4 + 6 * 0x4;
	uintptr_t blank = 0;
	uintptr_t jumpHeightOffset = 0x130;
	float currentZombieCordsValue[] = { 0, 0, 0 };
	uintptr_t p1WC = 0;
	uintptr_t p2WC = 0;
	uintptr_t p3WC = 0;
	uintptr_t p4WC = 0;
	uintptr_t p1LC = 0;
	uintptr_t p2LC = 0;
	uintptr_t p3LC = 0;
	uintptr_t p4LC = 0;
	uintptr_t p1TC = 0;
	uintptr_t p2TC = 0;
	uintptr_t p3TC = 0;
	uintptr_t p4TC = 0;
	uintptr_t p1FUC = 0;
	uintptr_t p2FUC = 0;
	uintptr_t p3FUC = 0;
	uintptr_t p4FUC = 0;
	uintptr_t p1WWC = 0;
	uintptr_t p2WWC = 0;
	uintptr_t p3WWC = 0;
	uintptr_t p4WWC = 0;
	uintptr_t p1KSC = 0;
	uintptr_t Camo = (address + 0x10E83880) + 0x1205A4;
	//uintptr_t Index = 0x1E5B6;//0x37860
	// Main Weapons
	vector<uintptr_t> p1W = { 49, 5, 11, 47, 26, 46, 29, 38, 54, 41, 17, 14, 43, 40, 32, 35, 34, 31, 2, 44, 57, 28, 45, 4, 15, 19, 25, 33, 48, 56, 21, 10, 12, 24, 27, 9, 8 };
	vector<uintptr_t> p2W = { 49, 5, 11, 47, 26, 46, 29, 38, 54, 41, 17, 14, 43, 40, 32, 35, 34, 31, 2, 44, 57, 28, 45, 4, 15, 19, 25, 33, 48, 56, 21, 10, 12, 24, 27, 9, 8 };
	vector<uintptr_t> p3W = { 49, 5, 11, 47, 26, 46, 29, 38, 54, 41, 17, 14, 43, 40, 32, 35, 34, 31, 2, 44, 57, 28, 45, 4, 15, 19, 25, 33, 48, 56, 21, 10, 12, 24, 27, 9, 8 };
	vector<uintptr_t> p4W = { 49, 5, 11, 47, 26, 46, 29, 38, 54, 41, 17, 14, 43, 40, 32, 35, 34, 31, 2, 44, 57, 28, 45, 4, 15, 19, 25, 33, 48, 56, 21, 10, 12, 24, 27, 9, 8 };
	// Tacticals
	vector<uintptr_t> p1T = { 39, 163, 120, 7, 20 };
	vector<uintptr_t> p2T = { 39, 163, 120, 7, 20 };
	vector<uintptr_t> p3T = { 39, 163, 120, 7, 20 };
	vector<uintptr_t> p4T = { 39, 163, 120, 7, 20 };
	// Lethals
	vector<uintptr_t> p1L = { 22, 50, 123, 13, 42 };
	vector<uintptr_t> p2L = { 22, 50, 123, 13, 42 };
	vector<uintptr_t> p3L = { 22, 50, 123, 13, 42 };
	vector<uintptr_t> p4L = { 22, 50, 123, 13, 42 };
	// Field Updgrades
	vector<uintptr_t> p1FU = { 296, 245, 295, 225, 285, 239 };
	vector<uintptr_t> p2FU = { 296, 245, 295, 225, 285, 239 };
	vector<uintptr_t> p3FU = { 296, 245, 295, 225, 285, 239 };
	vector<uintptr_t> p4FU = { 296, 245, 295, 225, 285, 239 };
	// Wonder Weapons
	vector<uintptr_t> p1WW = { 6, 350, 23, 36 };
	vector<uintptr_t> p2WW = { 6, 350, 23, 36 };
	vector<uintptr_t> p3WW = { 6, 350, 23, 36 };
	vector<uintptr_t> p4WW = { 6, 350, 23, 36 };
	// Kill Streaks
	vector<uintptr_t> p1KS = { 206, 68, 108, 149, 165, 293, 102, 64, 77, 72, 150 };
	vector<uintptr_t> p2KS = { 206, 68, 108, 149, 165, 293, 102, 64, 77, 72, 150 };
	vector<uintptr_t> p3KS = { 206, 68, 108, 149, 165, 293, 102, 64, 77, 72, 150 };
	vector<uintptr_t> p4KS = { 206, 68, 108, 149, 165, 293, 102, 64, 77, 72, 150 };
	// Camo Shit
	vector<unsigned int> camo1 = { 0xC3, 0x09 };
	vector<unsigned int> camo2 = { 0x22 };
	vector<unsigned int> camo3 = { 0x18 };
	vector<unsigned int> camo4 = { 0x0E };
	vector<unsigned int> camo5 = { 0x09 };
	uintptr_t camoPtr = address + 0x10E83880;
	uintptr_t cammoFuck = FindDMAAddy(discordOverlay, camoPtr, camoOffset);
	uintptr_t cammoFuck2 = FindDMAAddy(discordOverlay, camoPtr, camoOffset2);
	uintptr_t cammoFuck3 = FindDMAAddy(discordOverlay, camoPtr, camoOffset3);
	uintptr_t cammoFuck4 = FindDMAAddy(discordOverlay, camoPtr, camoOffset4);
	uintptr_t currentPlayerCords = FindDMAAddy(discordOverlay, playerBase, playerCordsOffset);
	//ReadProcessMemory(discordOverlay, (uintptr_t*)currentPlayerCords, &currentZombieCordsValue, sizeof(currentZombieCordsValue), nullptr);

	while (true)
	{
		
		if (driver->GetProcessID("BlackOpsColdWar.exe") == false)
		{
			exit(0);
		}
		/*
		*	Player 1 Features
		*/
		if (infiniteHealth)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + godMode, 0xA0);
		}
		if (infiniteHealth == false)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + godMode, 0x20);
		}
		if (infiniteAmmo)
		{
			for (uintptr_t a = 1; a < 6; a++)
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + ammo + (a * 0x4), 5);
			}
		}
		if (infinitePoints)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + points, 31222);
		}
		if (alwaysInstaKill)
		{
			for (uintptr_t i = 5; i < 200; i++)
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerPedBase) + 0x398 + (0x5F8 * i), 1);
			}
		}
		if (alwaysCrit)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + zombieCritAddr, -1);
		}
		if (playerRankXP)
		{
			driver->WriteMemory(address + rankXP + rankOffset, xpval);
			driver->WriteMemory(address + rankXP + rankOffset2,xpval);
		}
		if (playerWeaponXP)
		{
			driver->WriteMemory(address + weaponXP + weaponOffset, xpval);
		}
		if (jumpHeight)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(jumpHeightBase) + jumpHeightOffset, 200.f);
		}
		if (jumpHeight == false)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(jumpHeightBase) + jumpHeightOffset, 39.f);
		}
		if (p1WCycle)
		{
			if (GetAsyncKeyState(VK_NUMPAD1))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + setWeapon, p1W[p1WC]);
				p1WC++;
				Sleep(500);
			}
			if (p1WC == 37)
			{
				p1WC = 0;
			}
		}
		if (p1LCycle)
		{
			if (GetAsyncKeyState(0x4C))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + setWeapon + 1 * 0x40, p1L[p1LC]);
				p1LC++;
				Sleep(500);
			}
			if (p1LC == 5)
			{
				p1LC = 0;
			}
		}
		if (p1TCycle)
		{
			if (GetAsyncKeyState(0x54))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + setWeapon + 2 * 0x40, p1T[p1TC]);
				p1TC++;
				Sleep(500);
			}
			if (p1TC == 5)
			{
				p1TC = 0;
			}
		}
		if (p1FUCycle)
		{
			if (GetAsyncKeyState(0x37))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + setWeapon + 3 * 0x40, p1FU[p1FUC]);
				p1FUC++;
				Sleep(500);
			}
			if (p1FUC == 6)
			{
				p1FUC = 0;
			}
		}
		if (p1WWCycle)
		{
			if (GetAsyncKeyState(0x38))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + setWeapon, p1WW[p1WWC]);
				p1WWC++;
				Sleep(500);
			}
			if (p1WWC == 4)
			{
				p1WWC = 0;
			}
		}
		if (p1Speed)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + runSpeed, 2.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + runSpeed, 2.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + runSpeed, 2.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + runSpeed, 2.f);
		}
		if (p1Speed == false)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + runSpeed, 1.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + runSpeed, 1.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + runSpeed, 1.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + runSpeed, 1.f);
		}
		if (zombieTP)
		{
			for (uintptr_t i = 5; i < 200; i++)
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerPedBase) + 0x2D4 + (0x5F8 * i), currentZombieCordsValue);
			}
		}
		if (newZombieLocation)
		{
			ReadProcessMemory(discordOverlay, (uintptr_t*)currentPlayerCords, &currentZombieCordsValue, sizeof(currentZombieCordsValue), nullptr);
			newZombieLocation = false;
		}
		if (GetAsyncKeyState(0x5A))
		{
			ReadProcessMemory(discordOverlay, (uintptr_t*)currentPlayerCords, &currentZombieCordsValue, sizeof(currentZombieCordsValue), nullptr);
		}
		if (restartGame)
		{
			string CMDCOMMAND = "full_restart;";
			driver->WriteMemory((address + cmdBufferBase), CMDCOMMAND);
			driver->WriteMemory((address + cmdBufferBase) + CMDBB_Exec, true);
			restartGame = false;
		}
		if (disconnectGame)
		{
			string CMDCOMMAND = "disconnect;";
			driver->WriteMemory((address + cmdBufferBase), CMDCOMMAND);
			driver->WriteMemory((address + cmdBufferBase) + CMDBB_Exec, true);
			disconnectGame = false;
		}

		/*
		if (quickStart)
		{ 
			string CMDCOMMAND = "lobbyLaunchGame;";
			driver->WriteMemory((address + cmdBufferBase), CMDCOMMAND);
			driver->WriteMemory((address + cmdBufferBase) + CMDBB_Exec, true);
			quickStart = false;
		}
		*/
		if (blaznOneShot)
		{
			for (ULONG i = 0; i < 142; i++)
			{
				driver->WriteMemory(cammoFuck + (0x80 * i), camo1);
				driver->WriteMemory(cammoFuck + 0x09 + (0x80 * i), camo1);
				driver->WriteMemory(cammoFuck + 0x12 + (0x80 * i), camo1);
				driver->WriteMemory(cammoFuck + 0x1C + (0x80 * i), camo2);
				driver->WriteMemory(cammoFuck + 0x1D + (0x80 * i), camo2);
				driver->WriteMemory(cammoFuck + 0x28 + (0x80 * i), camo3);
				driver->WriteMemory(cammoFuck + 0x36 + (0x80 * i), camo4);
				driver->WriteMemory(cammoFuck + 0x41 + (0x80 * i), camo5);
				driver->WriteMemory(cammoFuck + 0x52 + (0x80 * i), camo5);
			}
			/*
			for (ULONG g = 0; g < 142; g++)
			{
				driver->WriteMemory((cammoFuck2 + (0x80 * (ULONG)g)), camo1);
				driver->WriteMemory((cammoFuck2 + 0x09 + (0x80 * (ULONG)g)), camo1);
				driver->WriteMemory((cammoFuck2 + 0x12 + (0x80 * (ULONG)g)), camo1);
				driver->WriteMemory((cammoFuck2 + 0x1C + (0x80 * (ULONG)g)), camo2);
				driver->WriteMemory((cammoFuck2 + 0x1D + (0x80 * (ULONG)g)), camo2);
				driver->WriteMemory((cammoFuck2 + 0x28 + (0x80 * (ULONG)g)), camo3);
				driver->WriteMemory((cammoFuck2 + 0x36 + (0x80 * (ULONG)g)), camo4);
				driver->WriteMemory((cammoFuck2 + 0x41 + (0x80 * (ULONG)g)), camo5);
				driver->WriteMemory((cammoFuck2 + 0x52 + (0x80 * (ULONG)g)), camo5);
			}
			for (ULONG s = 0; s < 142; s++)
			{
				driver->WriteMemory((cammoFuck3 + (0x80 * s)), camo1);
				driver->WriteMemory((cammoFuck3 + 0x09 + (0x80 * s)), camo1);
				driver->WriteMemory((cammoFuck3 + 0x12 + (0x80 * s)), camo1);
				driver->WriteMemory((cammoFuck3 + 0x1C + (0x80 * s)), camo2);
				driver->WriteMemory((cammoFuck3 + 0x1D + (0x80 * s)), camo2);
				driver->WriteMemory((cammoFuck3 + 0x28 + (0x80 * s)), camo3);
				driver->WriteMemory((cammoFuck3 + 0x36 + (0x80 * s)), camo4);
				driver->WriteMemory((cammoFuck3 + 0x41 + (0x80 * s)), camo5);
				driver->WriteMemory((cammoFuck3 + 0x52 + (0x80 * s)), camo5);
			}
			for (ULONG f = 0; f < 142; f++)
			{
				driver->WriteMemory((cammoFuck4 + (0x80 * f)), camo1);
				driver->WriteMemory((cammoFuck4 + 0x09 + (0x80 * f)), camo1);
				driver->WriteMemory((cammoFuck4 + 0x12 + (0x80 * f)), camo1);
				driver->WriteMemory((cammoFuck4 + 0x1C + (0x80 * f)), camo2);
				driver->WriteMemory((cammoFuck4 + 0x1D + (0x80 * f)), camo2);
				driver->WriteMemory((cammoFuck4 + 0x28 + (0x80 * f)), camo3);
				driver->WriteMemory((cammoFuck4 + 0x36 + (0x80 * f)), camo4);
				driver->WriteMemory((cammoFuck4 + 0x41 + (0x80 * f)), camo5);
				driver->WriteMemory((cammoFuck4 + 0x52 + (0x80 * f)), camo5);
			}
			*/
			blaznOneShot = false;
		}
		/*
		*	Player 2 Features
		*/
		if (p2infiniteHealth)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + godMode, 0xA0);
		}
		if (p2infiniteHealth == false)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + godMode, 0x20);
		}
		if (p2infiniteAmmo)
		{
			for (uintptr_t a = 1; a < 6; a++)
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + ammo + (a * 0x4), 5);
			}
		}
		if (p2infinitePoints)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + points, 33450);
		}
		if (p2alwaysCrit)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + zombieCritAddr, -1);
		}
		if (p2WCycle)
		{
			// Kb 4
			if (GetAsyncKeyState(VK_NUMPAD2))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + setWeapon, p2W[p2WC]);
				p2WC++;
				Sleep(500);
			}
			if (p2WC == 37)
			{
				p2WC = 0;
			}
		}
		if (p2LCycle)
		{
			// Kb 5
			if (GetAsyncKeyState(0x35))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + setWeapon + 1 * 0x40, p2L[p2LC]);
				p2LC++;
				Sleep(500);
			}
			if (p2LC == 5)
			{
				p2LC = 0;
			}
		}
		if (p2TCycle)
		{
			// Kb 6
			if (GetAsyncKeyState(0x36))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + setWeapon + 2 * 0x40, p2T[p2TC]);
				p2TC++;
				Sleep(500);
			}
			if (p2TC == 5)
			{
				p1TC = 0;
			}
		}
		if (p2FUCycle)
		{

			if (GetAsyncKeyState(0x32))
			{
				// Kb Num1
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + setWeapon + 3 * 0x40, p2FU[p2FUC]);
				p2FUC++;
				Sleep(500);
			}
			if (p2FUC == 6)
			{
				p2FUC = 0;
			}
		}
		if (p2WWCycle)
		{
			// Kb Num2
			if (GetAsyncKeyState(0x31))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + setWeapon, p2WW[p2WWC]);
				p2WWC++;
				Sleep(500);
			}
			if (p2WWC == 4)
			{
				p2WWC = 0;
			}
		}
		/*
		*	Player 3 Features
		*/
		if (p3infiniteHealth)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + godMode, 0xA0);
		}
		if (p3infiniteHealth == false)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + godMode, 0x20);
		}
		if (p3infiniteAmmo)
		{
			for (uintptr_t a = 1; a < 6; a++)
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + ammo + (a * 0x4), 5);
			}
		}
		if (p3infinitePoints)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + points, 32265);
		}
		if (p3alwaysCrit)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + zombieCritAddr, -1);
		}
		if (p3WCycle)
		{
			// Kb 9
			if (GetAsyncKeyState(VK_NUMPAD3))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + setWeapon, p3W[p3WC]);
				p3WC++;
				Sleep(500);
			}
			if (p3WC == 37)
			{
				p3WC = 0;
			}
		}
		if (p3LCycle)
		{
			// Kb 0
			if (GetAsyncKeyState(0x30))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + setWeapon + 1 * 0x40, p3L[p3LC]);
				p3LC++;
				Sleep(500);
			}
			if (p3LC == 5)
			{
				p3LC = 0;
			}
		}
		if (p3TCycle)
		{
			// Kb -
			if (GetAsyncKeyState(0xBD))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + setWeapon + 2 * 0x40, p3T[p3TC]);
				p3TC++;
				Sleep(500);
			}
			if (p3TC == 5)
			{
				p3TC = 0;
			}
		}
		if (p3FUCycle)
		{

			if (GetAsyncKeyState(VK_BROWSER_FAVORITES))
			{
				// Kb Num1
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + setWeapon + 3 * 0x40, p3FU[p3FUC]);
				p3FUC++;
				Sleep(500);
			}
			if (p3FUC == 6)
			{
				p3FUC = 0;
			}
		}
		if (p3WWCycle)
		{
			// Kb Num2
			if (GetAsyncKeyState(VK_BROWSER_STOP))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + setWeapon, p3WW[p3WWC]);
				p3WWC++;
				Sleep(500);
			}
			if (p3WWC == 4)
			{
				p3WWC = 0;
			}
		}
		/*
		*	Player 4 Features
		*/
		if (p4infiniteHealth)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + godMode, 0xA0);
		}
		if (p4infiniteHealth == false)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + godMode, 0xA0);
		}
		if (p4infiniteAmmo)
		{
			for (uintptr_t a = 1; a < 6; a++)
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + ammo + (a * 0x4), 5);
			}
		}
		if (p4infinitePoints)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + points, 36950);
		}
		if (p4alwaysCrit)
		{
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + zombieCritAddr, -1);
		}
		if (p3WCycle)
		{
			// Kb <
			if (GetAsyncKeyState(VK_NUMPAD4))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + setWeapon, p4W[p4WC]);
				p4WC++;
				Sleep(500);
			}
			if (p4WC == 37)
			{
				p4WC = 0;
			}
		}
		if (p3LCycle)
		{
			// Kb .
			if (GetAsyncKeyState(0xBE))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + setWeapon + 1 * 0x40, p4L[p4LC]);
				p4LC++;
				Sleep(500);
			}
			if (p4LC == 5)
			{
				p4LC = 0;
			}
		}
		if (p3TCycle)
		{
			// Kb /
			if (GetAsyncKeyState(0xBF))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + setWeapon + 2 * 0x40, p4T[p4TC]);
				p4TC++;
				Sleep(500);
			}
			if (p4TC == 5)
			{
				p4TC = 0;
			}
		}
		if (p3FUCycle)
		{

			if (GetAsyncKeyState(VK_GAMEPAD_DPAD_DOWN))
			{
				// Kb Num1
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + setWeapon + 3 * 0x40, p4FU[p4FUC]);
				p4FUC++;
				Sleep(500);
			}
			if (p4FUC == 6)
			{
				p4FUC = 0;
			}
		}
		if (p3WWCycle)
		{
			// Kb Num2
			if (GetAsyncKeyState(VK_NUMPAD8))
			{
				driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + setWeapon, p4WW[p4WWC]);
				p4WWC++;
				Sleep(500);
			}
			if (p4WWC == 4)
			{
				p4WWC = 0;
			}
		}
		if (GetAsyncKeyState(0x39))
		{
			/*
			*	Player 1 booleans
			*/
			
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + godMode, 0x20);
			
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(jumpHeightBase) + jumpHeightOffset, 39.f);
		
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + runSpeed, 1.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + runSpeed, 1.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + runSpeed, 1.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + runSpeed, 1.f);
		
			driver->WriteMemory(address + rankXP + rankOffset, 1.f);
			driver->WriteMemory(address + rankXP + rankOffset2, 1.f);
			
			driver->WriteMemory(address + weaponXP + weaponOffset, 1.f);
	
			/*
			*	Player 2 booleans
			*/
			
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * 0xB900 + godMode, 0x20);
	
			/*
			*	Player 3 booleans
			*/
			
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * 0xB900 + godMode, 0x20);
		
			/*
			*	Player 4 booleans
			*/
			
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * 0xB900 + godMode, 0x20);
		
		}
		if (GetAsyncKeyState(VK_HOME))
		{
			/*
			*	Player 1 booleans
			*/
			
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + godMode, 0x20);
			
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(jumpHeightBase) + jumpHeightOffset, 39.f);
		
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + runSpeed, 1.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * playerArray + runSpeed, 1.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * playerArray + runSpeed, 1.f);
			driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * playerArray + runSpeed, 1.f);
			
			driver->WriteMemory(address + rankXP + rankOffset, 1.f);
			driver->WriteMemory(address + rankXP + rankOffset2, 1.f);
		
			driver->WriteMemory(address + weaponXP + weaponOffset, 1.f);
		
			
			p2infiniteHealth = false; driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 1 * 0xB900 + godMode, 0x20);
		
			p3infiniteHealth = false; driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 2 * 0xB900 + godMode, 0x20);
		
		
			p4infiniteHealth = false; driver->WriteMemory(driver->ReadMemory<uintptr_t>(playerBase) + 3 * 0xB900 + godMode, 0x20);
		
			exit(0);
		}
	}

}
class Vector3 {
public:
	float x, y, z;
	Vector3() : x(0.f), y(0.f), z(0.f) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	void zombieCordsV()
	{
		x = -x;
		y = -y;
		z = -z;
	}
};

int main()
{

	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 500, 300, TRUE);
	

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



	//DoBypassInstaller();
	axeraMenuBody();



	main();

}






















