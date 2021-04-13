#pragma once

#include "../CxLib/Math/CXVector.h"

/// <summary>
/// A renderable object to pass into the CXScene
/// </summary>
class CXRenderObject
{
public:
	Vec3 position;

	//Quaternion rotation; // -> NEVER GONNA TOUCH THIS LOL (might)

	CXRenderObject(Vec3 _position);

	/// <summary>
	/// Get's the distance between the target position to the specified from Position
	/// </summary>
	virtual float GetSurfDistance(Vec3 fromPos);

	/// <summary>
	/// Get's the normal from the target point with the target precision (default as .01f)
	/// </summary>
	virtual Vec3 GetNormal(Vec3 pointOnSurface, float precision = .01f);
};