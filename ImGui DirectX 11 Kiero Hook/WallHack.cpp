#include "WallHack.h"
#include "framework/il2cpp-appdata.h"
#include "sackdata.h"
#include <iostream>
#include "Vector.h"
#define EntListBase 0xB35C3C
#define EntListBase2 0xB35CA8

app::PlayerData* GetPlayerData(UINT32 i)
{

    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    app::PlayerData* anus = (app::PlayerData*)offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 0x4,0x0 });
    return anus;
}


Vector2 WallHack::Renders(int i)
{

    offsetsM offsets; 
    UINT asddddd = i;
  if (offsets.GetPointerAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0xB35CA8, { 0x5C,0x0C, (UINT)0x10 + i * 4,  0x28 }) == reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0xB35CA8)
        return { -1, -1,-1 };/// vec 0
    ImVec2 posInScreenTrue;
    app::PlayerData* enemy = GetPlayerData(i); // saksak 
    app::PlayerData* my = (*app::Controll__TypeInfo)->static_fields->pl; // saksak 
    app::Vector3 posEnemy = enemy->fields.currPos;
    app::Vector3 projected = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, posEnemy, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
    app::String* asdz = (enemy->fields.name);
    WallHackNames* chars = (WallHackNames*)asdz;

    if (teamcheck == true)
    {

        if (my->fields.team == enemy->fields.team)
        {
            return { -1, -1,-1 };/// vec 07
        }
    }
    if (enemy->fields.health <= 1)
        return { -1, -1,-1 };/// vec 07
    if (projected.z <= 1.0f)
        return { -1, -1,-1 };/// vec 0
    if (enemy->fields.bstate == 5)
        return { -1,-1,-1 };


    posInScreenTrue.x = projected.x;
    posInScreenTrue.y = app::Screen_get_height(nullptr) - projected.y;

    if (enemy->fields.leg_limit == 46)
        return { posInScreenTrue.x ,posInScreenTrue.y,44,chars->Pname };
    if (enemy->fields.spawnprotect)
    {
        return { posInScreenTrue.x ,posInScreenTrue.y,3,chars->Pname };/// vec 07
    }
    /// vec 07

    Vector2 asd = { posInScreenTrue.x ,posInScreenTrue.y,0,chars->Pname };
    return asd;



}
