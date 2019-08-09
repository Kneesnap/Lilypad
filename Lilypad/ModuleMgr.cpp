#include "modulemgr.h"

ModuleManager *ModMgr = new ModuleManager();

MODULEINFO ModuleManager::getModuleInfo(char* szModule) {

	MODULEINFO lpmodinfo;
	HMODULE hModule = GetModuleHandleA(szModule);
	HANDLE hProcess = GetCurrentProcess();

	memset(&lpmodinfo, 0, sizeof(lpmodinfo));

	if (hModule != NULL && hProcess != NULL) {

		if (SUCCEEDED(GetModuleInformation(hProcess, hModule, &lpmodinfo, sizeof(MODULEINFO))))
			return lpmodinfo;
	}

	return lpmodinfo;
}