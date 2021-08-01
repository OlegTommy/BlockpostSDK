#include "includes.h"
#include <cmath>
#include <array>
#include <iostream>
#include "Vector.h"
//#include "framework/il2cpp-appdata.h"
#define EntListBase 0xB35C3C
#define EntListBase2 0xB35CA8

//58
class AngleView
{
private:
    Vector3 distA, angleXA, angleYA;
};

Vector2 AimBot::GetDistanceAndAngle(Vector3 startPOS, Vector3 endPOS)
{
    float deltaX = endPOS.x - startPOS.x;
    float deltaY = endPOS.y - startPOS.y - 0.1f;
    float deltaZ = endPOS.z - startPOS.z;

    float dist = sqrt(
        pow((endPOS.x - startPOS.x), 2.0) +
        pow((endPOS.y - startPOS.y), 2.0) +
        pow((endPOS.z - startPOS.z), 2.0));
    if (dist < 0)
    {
        dist = dist * -1;
    }

    float xzlength = sqrt((deltaX * deltaX) + (deltaZ * deltaZ));
    float angleX = atan2(deltaY, xzlength) * (-57.2957795);
    float angleY = atan2(deltaX, deltaZ) * (57.2957795);
    Vector2 ANAL = { angleX,angleY,dist };
    return  ANAL;
}


void SetView(Vector2 pos)
{
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));

    if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x40 }) != 0)
    {
        float* x = reinterpret_cast<float*>(offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x40 }));
        float* y = reinterpret_cast<float*>(offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x3C }));

        *x = pos.x;
        *y = pos.y;
    }
}
PlayerData* GetLocals()
{
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    PlayerData* uranus = (PlayerData*)offsets.GetPointerAddress(baseModule + EntListBase, { 0x5c, 0x13c , 0x0 });
    return uranus;
}

PlayerData* Gets(UINT32 i)
{
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll"))); 
    PlayerData* anus = (PlayerData*)offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 0x4,0x0 });
    return anus;
}
void AimBot::Render()
{



    GetMyPoss startpos;
    AngleView view;
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
   
    int health = 0;
  
    
    for (ULONG i = 0; i < 40; i++)
    {
        if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x28 }) == baseModule + EntListBase2)
            continue;

        PlayerData* enemy = Gets(i); // saksak 
        PlayerData* MyPlayer = GetLocals();
       
        if (enemy->Pos.x == 0)
            continue;
        if (enemy->team == MyPlayer->team && teamcheck == true)
            continue;
        
        cscamera* mycam = (cscamera*)(*app::Controll__TypeInfo)->static_fields->csCam;

            while (true)
            {
                if (!GetAsyncKeyState(VK_LBUTTON) && !GetAsyncKeyState(VK_LSHIFT) && toggle == true)
                    break;
                if (enemy->spawnprotect)
                    break;
                if (enemy->health <= 5)
                    break;
                if (mycam->camira == nullptr)
                    break;
                Vector3 as = enemy->Pos;
   
                Vector3 sack2 = mycam->camira->campos;
                if (sack2.x != -1 && sack2.y != -1 && sack2.z != -1)
                {
                    if (enemy->bstate == 2 || enemy->bstate == 3)
                    {
                        if (MyPlayer->bstate != 2 || MyPlayer->bstate != 3)
                        {
                            float SAH = 0.6;
                            sack2.y = sack2.y + SAH;
                        }
                    }
                    if (enemy->bstate != 2 || enemy->bstate != 3)
                    {
                        if (MyPlayer->bstate == 2 || MyPlayer->bstate == 3)
                        {
                            float SAH = 0.6;
                            sack2.y = sack2.y - SAH;
                        }
                    }
                    if (enemy->bstate == 4)
                    {
                        float SAH = 0.3;
                        sack2.y = sack2.y + SAH;
                    }
                    if (enemy->bstate != 5)
                    {
                        Vector2 GEYSEX = GetDistanceAndAngle(sack2, as);                       
                   

                        if (GEYSEX.d <= distanceFov)
                        {

                            dist = GEYSEX.d;
                            float x = *reinterpret_cast<float*>(offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x3c }));
                            float y = *reinterpret_cast<float*>(offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x40 }));
                            
                                
                                 mysackx = x;
                                 mysacky = y;  
                                float normdis = GEYSEX.x;
                                // -20 , 
                                //  20
                             mysacky = mysacky - normdis;


                                if (GEYSEX.y < 0)
                                {
                                    GEYSEX.y = 360 + GEYSEX.y;
                                }
                                if (x < 0)
                                {
                                    x = 360 + x;
                                }
                                // -20 , 20
                                mysackx = GEYSEX.y - x;
                  
                                
                                if (mysackx < -fov || mysackx > fov || mysacky < -fov  || mysacky > fov )
                                {
                                    break;
                                }
                                else {

                                    SetView(GEYSEX);
                                }
                                  
                                
                                
                            
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        
    }
}