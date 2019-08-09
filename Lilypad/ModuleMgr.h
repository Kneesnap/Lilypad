#ifndef _MOD_MANAGER_H
#define _MOD_MANAGER_H

#pragma once

#include <Windows.h>
#include <Psapi.h>

class ModuleManager {

public:
	ModuleManager() {};
	~ModuleManager() {};

	MODULEINFO getModuleInfo(_In_ char* szModule);
};

extern ModuleManager *ModMgr;

#endif