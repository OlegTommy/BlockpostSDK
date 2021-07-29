#include "includes.h"
#include <cmath>
#include <array>
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
    float deltaY = endPOS.y - startPOS.y - 2.3;
    float deltaZ = endPOS.z - startPOS.z;

    float dist = sqrt(
        pow((endPOS.x - startPOS.x), 2.0) +
        pow((endPOS.y - startPOS.y), 2.0) +
        pow((endPOS.z - startPOS.z), 2.0));


    float xzlength = sqrt((deltaX * deltaX) + (deltaZ * deltaZ));

    float angleX = atan2(deltaY, xzlength) * (-57.2957795);
    float angleY = atan2(deltaX, deltaZ) * (57.2957795);
    Vector2 ANAL = { angleX,angleY };
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

void AimBot::Render()
{
    GetMyPoss startpos;
    AngleView view;
    Name Nm;

    int Nym = *Nm.GetNumPlayer();
    if (Nym == 0)
        return;
    //EntListBase, { 0x5C,0x13c,0x14 }
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    int health =0;
    for (ULONG i = 0; i < Nym; i++)
    {
        if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x14 }) != 0 && offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x13c,0x14 }) != 0)
        {
            int teamMy = *(int*)offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x13c,0x14 });
            int TeamEnt = *(int*)offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4, 0x14 });
            if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x50 }) == 0 || teamMy == TeamEnt)
                continue;
            else
            {
                while (true)
                {

                    if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x28 }) != NULL)
                    {
                        health = *(int*)offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x28 });
                    }
                    else
                        break;
                  
                    if (health <= 0)
                        break;
                    float z, x, y;
                    //float z
                    if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x50 })!= NULL)
                    {
               x= *(float*)offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x50 });
                        if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x54 }) != NULL)
                        {
                            y= *(float*)offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x54 });
                            if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x58 }) != NULL)
                            {
                                z = *(float*)offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x58 });
                            }
                            else
                                break;
                        }
                        else
                            break;
                    }
                    else
                        break;

               
                    Vector3 as = { x,y,z };
                    Vector3 sack2 = startpos.Get();
                   
                        Vector2 GEYSEX = GetDistanceAndAngle(sack2, as);
                        SetView(GEYSEX);
                    
                    
                }
               
            }
        }     
    }
    
}

