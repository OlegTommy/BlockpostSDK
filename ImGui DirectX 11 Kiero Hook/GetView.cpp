#include "includes.h"
#define BaseAddr 0xB35C3C

DWORD* GetView::View()
{
	offsetsM offsets;
	uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
	DWORD* View = (DWORD*)offsets.GetPointerAddress(baseModule + BaseAddr, { 0x5C , 0x3C });
	return View;
}