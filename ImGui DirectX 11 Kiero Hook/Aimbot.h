#pragma once
#include "includes.h"
const float pi = 3.14159265358979323846f;

class Vector3
{
public:

    float x, y, z;

    Vector3() {};
    Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
    Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
    Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
    Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
    Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
    Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
    Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
    Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    Vector3 Normalize() const { return *this * (1 / Length()); }
    float Distance(const Vector3& rhs) const { return (*this - rhs).Length(); }
};

using vec3 = Vector3;

vec3 CalcAngle(vec3 src, vec3 dst)
{
    vec3 angles;

    vec3 delta = src - dst;
    float hyp = src.Distance(dst);
    angles.x = asin(delta.z / hyp) * 360.0f / pi;
    angles.y = atan2(delta.y, delta.x) * 360.0f / pi;
    angles.z = 0.0f;

    if (delta.x >= 0.0f)
        angles.y -= 360.0f;

    return angles;
}