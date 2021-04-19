#pragma once

#include "CXRenderBody.h"
#include "../../CxLib/Math/CXMath.h"

// -------------- SPHERE -------------- //

/// <summary>
/// A simple sphere
/// </summary>
class CXSphereRenderBody : public CXRenderBody
{
public:
	float radius;

public:
	CXSphereRenderBody(const Vec3& _position, const float& _radius);

	float GetSignedDistance(const Vec3& fromPos) const override;
};

// -------------- PLANE -------------- //

/// <summary>
/// A plane that extends infinitely
/// </summary>
class CXInfPlaneRenderBody : public CXRenderBody
{
public:
	CXInfPlaneRenderBody(const Vec3& _position);

	float GetSignedDistance(const Vec3& fromPos) const override;

	Vec3 GetNormal(const Vec3& pointOnSurface) const override;
};

// -------------- BOX -------------- //

/// <summary>
/// A simple box
/// </summary>
class CXBoxRenderBody : public CXRenderBody
{
public:
	Vec3 boxDimension;

public:
	CXBoxRenderBody(const Vec3& _position, const Vec3& boxDimension);

	float GetSignedDistance(const Vec3& fromPos) const override;
};