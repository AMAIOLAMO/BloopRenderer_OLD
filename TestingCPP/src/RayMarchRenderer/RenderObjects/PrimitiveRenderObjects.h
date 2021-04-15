#pragma once

#include "CXRenderObject.h"

class CXSphereRenderObject : public CXRenderObject
{
public:
	float radius;

public:
	CXSphereRenderObject(const Vec3& _position, const CXColor& _baseColor, float _radius);

	CXSphereRenderObject(const Vec3& _position, const CXColor& _baseColor,
		CXMaterial*& _material_Ptr, float _radius);

	float GetSurfDistance(const Vec3& fromPos) const override;
};



/// <summary>
/// A plane that extends infinitely
/// </summary>
class CXInfPlaneRenderObject : public CXRenderObject
{
public:

public:
	CXInfPlaneRenderObject(const Vec3& _position, const CXColor& _baseColor);

	float GetSurfDistance(const Vec3& fromPos) const override;

	/*Vec3 GetNormal(const Vec3& pointOnSurface) const override;*/
};