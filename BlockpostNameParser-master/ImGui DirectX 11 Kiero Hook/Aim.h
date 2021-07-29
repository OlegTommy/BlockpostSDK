#pragma once
#include "includes.h"

class AimBot
{
public:
	Vector2 GetDistanceAndAngle(Vector3 startPOS, Vector3 endPOS);
	void Render();
};