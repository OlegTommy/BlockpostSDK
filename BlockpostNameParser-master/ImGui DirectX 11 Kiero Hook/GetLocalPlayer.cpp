#include "includes.h"
#define EntListBase 0xB35CA8

DWORD* GetLocalPlayer::LocalPlayer()
{
	offsetsM offsets;
	uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
	DWORD* Entity = (DWORD*)offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x0C, 0x10 + 0 * 4 });
	return Entity;
}