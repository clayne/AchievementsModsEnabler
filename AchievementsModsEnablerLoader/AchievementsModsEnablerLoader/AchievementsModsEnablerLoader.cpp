#include "stdafx.h"
#define _SKSE64_

////// F4SE //////
#ifdef _F4SE_
#include "common\IPrefix.h"
#include "F4SE\F4SE\PluginAPI.h"
extern "C" __declspec(dllexport) bool F4SEPlugin_Query(const F4SEInterface * skse, PluginInfo * info)
{
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "AchievementsModsEnablerLoader";
	info->version = 1;

	return TRUE;
}

extern "C" __declspec(dllexport) bool F4SEPlugin_Load(const F4SEInterface * skse)
{
	// Get dll path.
	TCHAR DllFilePath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, DllFilePath);
	_tcscat_s(DllFilePath, MAX_PATH, L"\\Data\\Plugins\\Sumwunn\\AchievementsModsEnabler.dll");

	// Return if already loaded.
	if (GetModuleHandle(DllFilePath) != 0) return 0;

	// Load it.
	HMODULE hModule = LoadLibrary(DllFilePath);
	FARPROC Function01 = GetProcAddress(hModule, "SetF4SEMode");
	FARPROC Function02 = GetProcAddress(hModule, "Setup");

	// Call stuff.
	Function01();
	Function02();

	return TRUE;
}
#endif

////// SKSE64 //////
#ifdef _SKSE64_
#include "common\IPrefix.h"
#include "SKSE64\SKSE64\PluginAPI.h"
// For pre-AE
extern "C" __declspec(dllexport) bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
{
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "Achievements Mods Enabler Loader";
	info->version = 1;

	return TRUE;
}

// For AE
extern "C" {
	__declspec(dllexport) SKSEPluginVersionData SKSEPlugin_Version =
	{
		SKSEPluginVersionData::kVersion,
		1,
		"Achievements Mods Enabler Loader",
		"xSHADOWMANx / Sumwunn",
		"",
		SKSEPluginVersionData::kVersionIndependent_Signatures, // Skyrim version independent
		{ 0, 0 },
		0, // SKSE64 version independent
	};
};

extern "C" __declspec(dllexport) bool SKSEPlugin_Load(const SKSEInterface * skse)
{
	// Get dll path.
	TCHAR DllFilePath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, DllFilePath);
	_tcscat_s(DllFilePath, MAX_PATH, L"\\Data\\Plugins\\Sumwunn\\AchievementsModsEnabler.dll");

	// Return if already loaded.
	if (GetModuleHandle(DllFilePath) != 0) return FALSE;

	// Load it.
	HMODULE hModule = LoadLibrary(DllFilePath);
	// Prevent crash.
	if (!hModule)
		return FALSE;

	FARPROC Function01 = GetProcAddress(hModule, "SetSKSEMode");
	FARPROC Function02 = GetProcAddress(hModule, "Setup");

	// Call stuff.
	Function01();
	Function02();

	return TRUE;
}

#endif