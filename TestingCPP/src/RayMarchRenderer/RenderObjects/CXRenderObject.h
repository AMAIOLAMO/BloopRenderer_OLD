#pragma once

#include <math.h>
#include "../../CxLib/Math/CXVector.h"
#include "../../CxLib/BitMap/CXColor.h"

/// <summary>
/// A renderable object to pass into the CXScene
/// </summary>
class CXRenderObject
{
public:
	Vec3 position;
	CXColor baseColor;

public:
	//Quaternion rotation; // -> NEVER GONNA TOUCH THIS LOL (might)

	CXRenderObject(const Vec3& _position, const CXColor& _baseColor);

	/// <summary>
	/// Deep copies from another renderer object
	/// </summary>
	CXRenderObject(const CXRenderObject& other);

	/// <summary>
	/// Get's the distance between the target position to the specified from Position
	/// </summary>
	virtual float GetSurfDistance(const Vec3& fromPos) const abstract = 0;

	/// <summary>
	/// Get's the material color of this point on surface
	/// </summary>
	virtual CXColor GetMaterialColor(const Vec3& pointOnSurface) const;

	/// <summary>
	/// Get's the normal from the target point with the target precision (default as .01f)
	/// </summary>
	virtual Vec3 GetNormal(const Vec3& pointOnSurface) const;
};