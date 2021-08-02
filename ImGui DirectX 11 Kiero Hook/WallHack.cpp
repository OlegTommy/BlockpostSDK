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
        app::PlayerData* ÿ = (*app::Controll__TypeInfo)->static_fields->pl; // saksak 
        if (teamcheck == true)
        {
         
            if (ÿ->fields.team == enemy->fields.team)
            {
                return { -1, -1,-1 };/// vec 07
            }
        }

        if (enemy->fields.health <= 1)
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
  //      app::Client* aszzzz = (*app::Client__TypeInfo)->static_fields->cs;
        app::String* asdz= (enemy->fields.name);
    //    app::Client_send_chatmsg(aszzzz , 0, enemy->fields.name, nullptr);
        WallHackNames* chars = (WallHackNames*)asdz;
    
 
        if (enemy->fields.spawnprotect)
        {
            return { posInScreenTrue.x ,posInScreenTrue.y,3,chars->Pname };/// vec 07
        }
        Vector2 asd = { posInScreenTrue.x ,posInScreenTrue.y,0,chars->Pname };
            return asd;
    
        
    
}