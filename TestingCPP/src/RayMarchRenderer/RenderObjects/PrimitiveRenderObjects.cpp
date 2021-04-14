#include "PrimitiveRenderObjects.h"

CXSphereRenderObject::CXSphereRenderObject(Vec3 _position, float _radius) :
	CXRenderObject(position), radius(_radius) {}

float CXSphereRenderObject::GetSurfDistance(Vec3 fromPos) const
{
	return (position - fromPos).GetLength() - radius;
}