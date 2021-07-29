#pragma once
#include "includes.h"
#include <string>

class Name
{
public:
	char* GetName(ULONG i);
	void Render();
	int* GetNumPlayer();
	bool togle = false;
};