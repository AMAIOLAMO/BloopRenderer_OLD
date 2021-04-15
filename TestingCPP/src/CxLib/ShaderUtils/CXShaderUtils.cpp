#include "CXShaderUtils.h"

Vec3 CXShaderUtils::Reflect(const Vec3& incidentVec, const Vec3& normalVec)
{
	// incident - 2(dot(incident, normal)) * normal;
	return incidentVec - normalVec * 2 * Vec3::Dot(incidentVec, normalVec);
}