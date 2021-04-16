#pragma once
#include "../../CxLib/Math/CXVector.h"

/// <summary>
/// This class is used to be group with material :D
/// which stores the SDF function (signed distance function and other stuff :P)
/// </summary>
class CXRenderBody
{
public:
	Vec3 position;

public:
	CXRenderBody(const Vec3& _position);

	/// <summary>
	/// Deep copies from another renderer object
	/// </summary>
	CXRenderBody(const CXRenderBody& other);

	~CXRenderBody();

	/// <summary>
	/// Get's the distance between the target position to the specified from Position
	/// </summary>
	virtual float GetSignedDistance(const Vec3& fromPos) const abstract = 0;

	/// <summary>
	/// Get's the normal from the target point with the target precision (default as .01f)
	/// </summary>
	virtual Vec3 GetNormal(const Vec3& pointOnSurface) const;
};