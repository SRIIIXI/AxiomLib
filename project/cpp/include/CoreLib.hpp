#pragma once

#if defined(_WIN32) || defined(WIN32) || defined (_WIN64) || defined (WIN64)

#include <windows.h>
#include <SDKDDKVer.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);

#else

#endif
