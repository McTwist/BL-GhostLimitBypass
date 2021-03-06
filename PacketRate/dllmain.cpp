#include <Windows.h>
#include <stdio.h>
#include "detours/detours.h"
#include "torque.h"
typedef char(*btc)(int* t);
MologieDetours::Detour<btc> *detour_windowFull = NULL;
char hook_getFinishedInitialGhost(int* t) {
	return 0;
}
bool init() {
	if (!torque_init()) return false;
	detour_windowFull = new MologieDetours::Detour<btc>((btc)0x5CA5D0, hook_getFinishedInitialGhost);
	return true;
}
bool deinit() {
	if (detour_windowFull != NULL) {
		delete detour_windowFull;
	}
	return true;
}
int __stdcall DllMain(HINSTANCE h, unsigned long reason, void* reserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		return init();
	case DLL_PROCESS_DETACH:
		return deinit();
	default:
		return true;
	}
}
extern "C" void __declspec (dllexport) __cdecl placeholder(void) {
}