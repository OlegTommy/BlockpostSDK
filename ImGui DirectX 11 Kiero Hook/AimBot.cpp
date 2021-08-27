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
    app::Controll__StaticFields* controll = (*app::Controll__TypeInfo)->static_fields;
    controll->rx = pos.y;
    controll->ry = pos.x;
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
        app::PlayerData* MyPlayer = (*app::Controll__TypeInfo)->static_fields->pl;

        if (enemy->curPos.x == 0)
            continue;
        if (enemy->team == MyPlayer->fields.team && teamcheck == true)
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
            if (enemy->bstate == 5)
                break;
           // if (enemy->leg_limit == 45)
              //  break;

            Vector3 enemypos = enemy->curPos;
            Vector3 mypos = mycam->camira->campos;

            if (mypos.x != -1 && mypos.y != -1 && mypos.z != -1)
            {
                if (enemy->bstate == 2 || enemy->bstate == 3)
                {
                    if (MyPlayer->fields.bstate != 2 || MyPlayer->fields.bstate != 3)
                    {
                        float SAH = 0.6;
                        mypos.y = mypos.y + SAH;
                    }
                }

                if (enemy->bstate == 4)
                {
                    float SAH = 0.3;
                    mypos.y = mypos.y + SAH;
                }
                if (enemy->bstate != 5)
                {
                    Vector2 AngletoTarger = GetDistanceAndAngle(mypos, enemypos);


                    if (AngletoTarger.d <= distanceFov)
                    {
                        app::Controll__StaticFields* controll = (*app::Controll__TypeInfo)->static_fields;
                        dist = AngletoTarger.d;
                        float x = controll->rx;
                        float y = controll->ry;
                        mysackx = x;
                        mysacky = y;

                        float normdis = AngletoTarger.x;
                        // -20 , 
                        //  20
                        mysacky = mysacky - normdis;


                        if (AngletoTarger.y < 0)
                        {
                            AngletoTarger.y = 360 + AngletoTarger.y;
                        }
                        if (x < 0)
                        {
                            x = 360 + x;
                        }
                        // -20 , 20
                        mysackx = AngletoTarger.y - x;


                        if (mysackx < -fov || mysackx > fov || mysacky < -fov || mysacky > fov)
                        {
                            break;
                        }
                        else {

                            SetView(AngletoTarger);
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
