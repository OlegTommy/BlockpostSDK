#pragma once
#include "VectorsSdk.hpp"
#include <cstdint>
#include "Memory.hpp"
#include "Offsets.hpp"

namespace UnityEngine {
	class RaycastHit {
	public:
		Vector3 Point, Normal;
		std::uint32_t FaceID;
		float Distance;
		Vector2 UV;
		std::int32_t Collider;
	};
	class Physics {
	public:
		static bool Linecast(Vector3 start, Vector3 end, std::add_pointer_t<RaycastHit> hit_info) {
			return Memory::FUNCTION_CAST<bool, Vector3, Vector3, std::add_pointer_t<RaycastHit>>(Offsets::Methods::Physics::Linecast, start, end, hit_info);
		}
	};
};