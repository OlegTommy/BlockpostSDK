#include "WallHack.h"
#include "framework/il2cpp-appdata.h"
#include "sackdata.h"
#include <iostream>

#define EntListBase 0xB35C3C
#define EntListBase2 0xB35CA8

sackdata* Gets(UINT32 i)
{
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    sackdata* anus = (sackdata*)offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 0x4,0x0 });
    return anus;
}

inline bool WorldToScreen(app::Vector3 pos, ImVec2* out)
{
    app::Vector3 projected = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, pos, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
    if (projected.z <= 1.0f)
        return false;

    out->x = projected.x;
    out->y = app::Screen_get_height(nullptr) - projected.y;
    return true;
}
void WallHack::Render()
{
   
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    for (ULONG i = 0; i < 40; i++)
    {
        if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x28 }) == baseModule + EntListBase2)
            continue;
        sackdata* enemy = Gets(i); // saksak 
        float x, y, z;
        x = enemy->Pos.x;
        y = enemy->Pos.y;
        z = enemy->Pos.z;
        app::Vector3 posEnemy = { x,y,z };
        ImVec2 posInScreenTrue;

        app::Vector3 projected = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, posEnemy, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
        if (projected.z <= 1.0f)
            continue;
        posInScreenTrue.x = projected.x;
        posInScreenTrue.y = app::Screen_get_height(nullptr) - projected.y;
        pos.x = posInScreenTrue.x;
        pos.y = posInScreenTrue.y;
        std::cout << "pos x: " << posInScreenTrue.x << "\n" << "pos y: " << posInScreenTrue.y << "\n";
        if (i >= 40)
        {
            return;
        }
        
    }	
}