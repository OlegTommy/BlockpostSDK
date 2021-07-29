#pragma once
#include <winnt.h>
#include <type_traits>
#include "UnityEngine.hpp"

class Hooks {
public:
	VOID Initialize() const;
	VOID Release() const;
private:
	static BOOL Raycast(Vector3 pos, Vector3 dir, std::add_pointer_t<UnityEngine::RaycastHit> hit, float dist);