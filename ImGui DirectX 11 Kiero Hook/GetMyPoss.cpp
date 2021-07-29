#include "includes.h"
#include <iostream>
#define LocalPlayerBase 0xB35C3C
#include "Vector.h"
Vector3 GetMyPoss::Get()
{
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));

    if (offsets.GetPointerAddress(baseModule + LocalPlayerBase, { 0x5c, 0x13c, 0x50 }) != NULL && offsets.GetPointerAddress(baseModule + LocalPlayerBase, { 0x5c, 0x13c, 0x54 }) != NULL && offsets.GetPointerAddress(baseModule + LocalPlayerBase, { 0x5c, 0x13c, 0x58 }) != NULL)
    {
        GetMyPoss::x = *(float*)offsets.GetPointerAddress(baseModule + LocalPlayerBase, { 0x5c, 0x13c, 0x50 });
        GetMyPoss::y = *(float*)offsets.GetPointerAddress(baseModule + LocalPlayerBase, { 0x5c, 0x13c, 0x54 });
        GetMyPoss::z = *(float*)offsets.GetPointerAddress(baseModule + LocalPlayerBase, { 0x5c, 0x13c, 0x58 });
        return { GetMyPoss::x, GetMyPoss::y, GetMyPoss::z };
    }
    return {-1,-1,-1};
}