#pragma once
#include "includes.h"
class PlayerDataArray
{
public:
	char pad_0012[0xF]; //0x00c
	PlayerData* Player[40]; //0x0010
};
