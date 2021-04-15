#include "PrimitiveRenderObjects.h"

// -------------------------- SPHERE -------------------------- //

CXSphereRenderObject::CXSphereRenderObject(const Vec3& _position, const CXColor& _baseColor, float _radius) :
	CXRenderObject(_position, _baseColor), radius(_radius) {}

CXSphereRenderObject::CXSphereRenderObject(const Vec3& _position, const CXColor& _baseColor,
	CXMaterial*& _material_Ptr, float _radius) :
	CXRenderObject(_position, _baseColor, _material_Ptr), radius(_radius) {}


float CXSphereRenderObject::GetSurfDistance(const Vec3& fromPos) const
{
	return (position - fromPos).GetLength() - radius;
}

// -------------------------- PLANE -------------------------- //

CXInfPlaneRenderObject::CXInfPlaneRenderObject(const Vec3& _position, const CXColor& _baseColor) :
	CXRenderObject(_position, _baseColor) {}

float CXInfPlaneRenderObject::GetSurfDistance(const Vec3& fromPos) const
{
	return fromPos.y  - position.y;
}