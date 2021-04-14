#include "CXRenderObject.h"

CXRenderObject::CXRenderObject(const Vec3& _position) :
	position(_position) {}

CXRenderObject::CXRenderObject(const CXRenderObject& other) :
	position(other.position) {}

static const float Epsilon = 1e-3f;
static const float TwoEpsilon = Epsilon * 2.0f;

//stole from Gary (thx Gary :D)
Vec3 CXRenderObject::GetNormal(const Vec3& pointOnSurface) const
{
	//a static so compiler won't create each time when we call this function
	float centerDist = GetSurfDistance(pointOnSurface);

	auto SampleClosest = [&](const Vec3& epsilonVec) // pass by reference
	{ return GetSurfDistance(pointOnSurface + epsilonVec) - centerDist; };

	Vec3 xEpsilonVec = Vec3(Epsilon, 0, 0);
	Vec3 yEpsilonVec = Vec3(0, Epsilon, 0);
	Vec3 zEpsilonVec = Vec3(0, 0, Epsilon);

	float xNormal = (SampleClosest(xEpsilonVec) - SampleClosest(-xEpsilonVec)) / TwoEpsilon;
	float yNormal = (SampleClosest(yEpsilonVec) - SampleClosest(-yEpsilonVec)) / TwoEpsilon;
	float zNormal = (SampleClosest(zEpsilonVec) - SampleClosest(-zEpsilonVec)) / TwoEpsilon;

	return Vec3(xNormal, yNormal, zNormal);
}