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
	Vec3 lookDirection;

	CXCamera(Vec3 _position, Vec3 _lookDirection);
	CXCamera(const CXCamera& other);
};