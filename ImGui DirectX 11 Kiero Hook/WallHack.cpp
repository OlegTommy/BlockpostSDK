#include "WallHack.h"
#include "framework/il2cpp-appdata.h"
#include "sackdata.h"
#include <iostream>
#include "Vector.h"
#define EntListBase 0xB35C3C
#define EntListBase2 0xB35CA8
app::PlayerData* GetLocals()
{
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    app::PlayerData* uranus = (app::PlayerData*)offsets.GetPointerAddress(baseModule + EntListBase, { 0x5c, 0x13c , 0x0 });
    return uranus;
}

app::PlayerData* GetPlayerData(UINT32 i)
{
  
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    app::PlayerData* anus = (app::PlayerData*)offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 0x4,0x0 });
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
Vector2 WallHack::Renders(int i)
{
   
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    UINT asddddd = i;
    if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + asddddd * 4,  0x28 }) == baseModule + EntListBase2)
        return { -1, -1,-1 };/// vec 0
        app::PlayerData* enemy = GetPlayerData(i); // saksak 
        if (GetLocals()->fields.team == enemy->fields.team)
        {
            return { -1, -1,-1 };/// vec 07
        }
        app::Vector3 posEnemy = enemy->fields.Pos;
      //  int32_t a = enemy->fields.team;
        ImVec2 posInScreenTrue;

        app::Vector3 projected = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, posEnemy, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
        if (projected.z <= 1.0f)
            return { -1, -1,-1 };/// vec 0
        posInScreenTrue.x = projected.x;
        posInScreenTrue.y = app::Screen_get_height(nullptr) - projected.y;
        if (enemy->fields.team == 1)
            return { posInScreenTrue.x ,posInScreenTrue.y,3 };
        Vector2 asd = { posInScreenTrue.x ,posInScreenTrue.y,0 };
            return asd;
    
        
    
}