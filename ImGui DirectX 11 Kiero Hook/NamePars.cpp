#include "includes.h"
#include <iostream>
#include <string>
#include "Settings.h"
#define EntListBase 0xB35CA8


int* Name::GetNumPlayer()
{
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    if (offsets.GetPointerAddress(baseModule + 0xB35E38, { 0x5C,0x40 }) != 0)
    {
        int* Num = (int*)offsets.GetPointerAddress(baseModule + 0xB35E38, { 0x5C,0x40 });
        return Num;
    }
    
}


char* Name::GetName(ULONG i)
{
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    char* Entity = (char*)offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x0C, 0x10 + i * 4,  0x18, 0xC });
    int Length = (int)offsets.GetPointerAddress(baseModule + EntListBase, { 0x5C,0x0C, 0x10 + i * 4,  0x18, 0x8 });

    if (Length != 24 && *(int*)Length < 30)
    {
        for (int d = 0; d < *(int*)Length * 2; d++)
        {
            if ((Entity) == nullptr)
                continue;
            else {
                std::cout << Entity + d;
            }
        }
        std::cout << std::endl;
        return Entity;
    }
}

void Name::Render()
{   
    
    Name Nm;
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);  
        if (togle)
        {
            ULONG Nym = *Nm.GetNumPlayer();
            for (ULONG i = 0; i < Nym; ++i)
            {
                Nm.GetName(i);

            }
            std::cout << "----------------------------" << std::endl;
            togle = false;
           
        }
        Sleep(10);      
}