#include "PrimitiveRenderObjects.h"

// -------------------------- SPHERE -------------------------- //

CXSphereRenderBody::CXSphereRenderBody(const Vec3& _position, const float& _radius) :
	CXRenderBody(_position), radius(_radius) {}

float CXSphereRenderBody::GetSignedDistance(const Vec3& fromPos) const
{
	return (position - fromPos).GetLength() - radius;
}

// -------------------------- PLANE -------------------------- //

CXInfPlaneRenderBody::CXInfPlaneRenderBody(const Vec3& _position) :
	CXRenderBody(_position) {}

inline float CXInfPlaneRenderBody::GetSignedDistance(const Vec3& fromPos) const
{
	return fromPos.y  - position.y;
}

inline Vec3 CXInfPlaneRenderBody::GetNormal(const Vec3& pointOnSurface) const
{
	//always facing up :D
	return Vec3(0, 1, 0);
}

// -------------------------- BOX -------------------------- //

CXBoxRenderBody::CXBoxRenderBody(const Vec3& _position, const Vec3& _boxDimension) :
	CXRenderBody(_position), boxDimension(_boxDimension) {}


static float MaxZeroVecFunc(float val)
{
	return CXMath::Max(val, .0f);
}

float CXBoxRenderBody::GetSignedDistance(const Vec3& fromPos) const
{
	Vec3 absPos(fromPos - position);

	//we absolute every single axis
	absPos.Map(fabsf);

	Vec3 q = absPos - boxDimension;

	q.Map(MaxZeroVecFunc);

	return q.GetLength() + CXMath::Min(CXMath::Max(q.x, CXMath::Max(q.y, q.z)), .0f);
}
