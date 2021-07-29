#pragma once
#include "includes.h"
#include "Vector.h"
class AimBot
{
public:
	Vector2 GetDistanceAndAngle(Vector3 startPOS, Vector3 endPOS);
	void Render();
	bool toggle = false;
	bool teamcheck = false;
	float distanceFov = 40;
	float fov = 1;
	float mysackx;
	float mysacky;
	float dist;
};