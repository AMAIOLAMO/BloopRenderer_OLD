#pragma once

#include "../Math/CXVector.h"

class CXShaderUtils
{
public:
	/// <summary>
	/// get's the reflection of a vector using a normal vector - (MUST BE NORMALIZED)
	/// </summary>
	Vec3 Reflect(const Vec3& incidentVec, const Vec3& normalVec);
};