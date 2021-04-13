#include "CXRenderObject.h"

CXRenderObject::CXRenderObject(Vec3 _position) :
	position(_position) {}

float CXRenderObject::GetSurfDistance(Vec3 fromPos)
{
	return 0.0f;
}

Vec3 CXRenderObject::GetNormal(Vec3 pointOnSurface, float precision)
{
	return Vec3(0, 0, 0);
}
