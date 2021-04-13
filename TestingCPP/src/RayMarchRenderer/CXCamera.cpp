#include "CXCamera.h"

CXCamera::CXCamera(Vec3 _position, float _farViewDistance) :
	position(_position), farViewDistance(_farViewDistance) {}

CXCamera::CXCamera(const CXCamera& other) :
	position(other.position), farViewDistance(other.farViewDistance) {}

Vec3 CXCamera::GetRayDirection(float uv_x, float uv_y) const
{
	//get's the uv and normalize it then return the sphere like direction :D (z as forward)
	return Vec3::GetNormalized(Vec3(uv_x, uv_y, 1));
}
