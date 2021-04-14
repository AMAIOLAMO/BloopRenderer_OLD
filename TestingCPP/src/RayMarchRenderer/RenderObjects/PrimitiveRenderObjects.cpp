#include "PrimitiveRenderObjects.h"

// -------------------------- SPHERE -------------------------- //

CXSphereRenderObject::CXSphereRenderObject(const Vec3& _position, float _radius) :
	CXRenderObject(_position), radius(_radius) {}

float CXSphereRenderObject::GetSurfDistance(const Vec3& fromPos) const
{
	return (position - fromPos).GetLength() - radius;
}

// -------------------------- PLANE -------------------------- //

CXInfPlaneRenderObject::CXInfPlaneRenderObject(const Vec3& _position) : CXRenderObject(_position) {}

float CXInfPlaneRenderObject::GetSurfDistance(const Vec3& fromPos) const
{
	return fromPos.y  - position.y;
}