#include "PrimitiveRenderObjects.h"

// -------------------------- SPHERE -------------------------- //

CXSphereRenderBody::CXSphereRenderBody(const Vec3& _position, const float& _radius) :
	CXRenderBody(_position), radius(_radius) {}

float CXSphereRenderBody::GetSignedDistance(const Vec3& fromPos) const
{
	return (position - fromPos).GetLength() - radius;
}

// -------------------------- PLANE -------------------------- //

float CXInfPlaneRenderBody::GetSignedDistance(const Vec3& fromPos) const
{
	return fromPos.y  - position.y;
}

Vec3 CXInfPlaneRenderBody::GetNormal(const Vec3& pointOnSurface) const
{
	//always facing up :D
	return Vec3(0, 1, 0);
}
