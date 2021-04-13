#include "CXRenderObject.h"

CXRenderObject::CXRenderObject(Vec3 _position) :
	position(_position) {}

CXRenderObject::CXRenderObject(const CXRenderObject& other) :
	position(other.position) {}

float CXRenderObject::GetSurfDistance(Vec3 fromPos) const
{
	const float SPHERE_SIZE = 1.0f;

	//THIS IS A TEST! A TEST SPHERE
	return (position - fromPos).GetLength() - SPHERE_SIZE;
	//return 0.0f;
}

Vec3 CXRenderObject::GetNormal(Vec3 pointOnSurface, float precision) const
{
	float surfDist = GetSurfDistance(pointOnSurface);

	float xNormal = surfDist - GetSurfDistance(pointOnSurface + Vec3(precision, 0, 0));
	float yNormal = surfDist - GetSurfDistance(pointOnSurface + Vec3(0, precision, 0));
	float zNormal = surfDist - GetSurfDistance(pointOnSurface + Vec3(0, 0, precision));

	return Vec3::GetNormalized(Vec3(xNormal, yNormal, zNormal));
}
