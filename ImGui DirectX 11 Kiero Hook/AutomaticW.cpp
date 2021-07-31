
#include "includes.h"


// GameAssembly.dll+2D8DB5 "83 7F 60 ? 75 ? 8B 0D" automatic
//  GameAssembly.dll + 2E0C24 distance 2B 56 ? 0F 57 DB
  // GameAssembly.dll+2E0BBD 6690C029 2B 46 ? 66 0F 6E C8
 void AutomaticW::Render()
{
	offsetsM offsets;
	DWORD OldProtection;
	uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));

	uintptr_t Injectionpoint = baseModule + 0x2D8DB5;
	uintptr_t DistanceInj = baseModule + 0x2E0C24;
	uintptr_t AcurInj = baseModule + 0x2E0BBD;
	VirtualProtect((LPVOID)Injectionpoint, 4, 0x40, &OldProtection);
	VirtualProtect((LPVOID)DistanceInj, 4, 0x40, &OldProtection);
	VirtualProtect((LPVOID)AcurInj, 4, 0x40, &OldProtection);
  BYTE* Bye = reinterpret_cast<BYTE*>(Injectionpoint);
  *Bye = 0x3;
  UINT* dst = reinterpret_cast<UINT*>(DistanceInj);
  *dst = 0x0F90F229;
  UINT* acurac = reinterpret_cast<UINT*>(AcurInj);
  *acurac = 0x6690C029;
  // GameAssembly.dll+2E0BBD 6690C029 2B 46 ? 66 0F 6E C8

  return;
}
