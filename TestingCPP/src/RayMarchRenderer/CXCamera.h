#pragma once
#include "../CxLib/Math/CXVector.h"

//NOT IN USE!!

/// <summary>
/// A basic camera that stores the basic information of a camera and a lot of helper functions
/// </summary>
class CXCamera
{
public:
	Vec3 position;
	float farViewDistance;

	CXCamera(Vec3 _position, float _farViewDistance);
	CXCamera(const CXCamera& other);

	/// <summary>
	/// Get's ray direction of this camera using a uv screen coordinate :D
	/// (REMEMBER uv_x and uv_y ARE IN PERCENTAGE WITH THE WHOLE PICTURE)
	/// </summary>
	Vec3 GetRayDirection(float uv_x, float uv_y) const;
};