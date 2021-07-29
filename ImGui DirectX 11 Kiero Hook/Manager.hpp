#pragma once
#include "VectorsSdk.hpp"
#include <vector>
#include "UnityEngine.hpp"

inline bool MultipleLineOfSight(std::vector<Vector3> positions, Vector3 src) {
	static UnityEngine::RaycastHit RaycastHit;

	for (Vector3 position : positions)
		if (!UnityEngine::Physics::Linecast(position, src, &RaycastHit))
			return true;

	return false;
}

inline bool LineOfSight(Vector3 position, Vector3 src) {
	static UnityEngine::RaycastHit RaycastHit;
	return !UnityEngine::Physics::Linecast(position, src, &RaycastHit);
}