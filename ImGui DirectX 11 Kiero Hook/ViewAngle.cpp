#include "includes.h"
#define EntListBase 0xB35C3C

float ViewAngle::Get()
{
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));

    ViewAngle::x = *(float*)offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x3C });
    ViewAngle::y = *(float*)offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x40 });
    return ViewAngle::x, ViewAngle::y;
}