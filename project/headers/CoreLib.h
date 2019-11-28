#include "Base64.h"
#include "KeyValue.h"
#include "List.h"
#include "Map.h"
#include "Node.h"
#include "Queue.h"
#include "Stack.h"
#include "StringEx.h"
#include "Tree.h"

#if defined(_WIN32) || defined(WIN32) || defined (_WIN64) || defined (WIN64)

#include <windows.h>
#include <SDKDDKVer.h>

BOOL APIENTRY DllMain(HMODULE /* hModule */, DWORD ul_reason_for_call, LPVOID /* lpReserved */);

#else

#endif
