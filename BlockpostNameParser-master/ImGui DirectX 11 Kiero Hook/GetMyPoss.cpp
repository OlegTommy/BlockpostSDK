#include "includes.h"
#include <iostream>
#define LocalPlayerBase 0xB35C3C

Vector3 GetMyPoss::Get()
{
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));

            GetMyPoss::x = *(float*)offsets.GetPointerAddress(baseModule + LocalPlayerBase, { 0x5c, 0x13c, 0x50 });
            GetMyPoss::y = *(float*)offsets.GetPointerAddress(baseModule + LocalPlayerBase, { 0x5c, 0x13c, 0x54 });
            GetMyPoss::z = *(float*)offsets.GetPointerAddress(baseModule + LocalPlayerBase, { 0x5c, 0x13c, 0x58 });
            return { GetMyPoss::x, GetMyPoss::y, GetMyPoss::z };       
       
    
   
}