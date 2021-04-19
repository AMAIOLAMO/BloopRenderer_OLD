#include "CXRenderBody.h"

CXRenderBody::CXRenderBody(const Vec3& _position) :
	position(_position) {}

CXRenderBody::CXRenderBody(const CXRenderBody& other) :
	position(other.position) {}

CXRenderBody::~CXRenderBody() {}

static const float Epsilon = 1e-4f;
static const float TwoEpsilon = Epsilon * 2.0f;

Vec3 CXRenderBody::GetNormal(const Vec3& point) const
{
	//a static so compiler won't create each time when we call this function
	float centerDist = GetSignedDistance(point);

	auto SampleClosest = [&](const Vec3& epsilonVec) // pass by reference
	{ return GetSignedDistance(point + epsilonVec) - centerDist; };

	Vec3 xEpsilonVec = Vec3(Epsilon, 0, 0);
	Vec3 yEpsilonVec = Vec3(0, Epsilon, 0);
	Vec3 zEpsilonVec = Vec3(0, 0, Epsilon);

	float xNormal = (SampleClosest(xEpsilonVec) - SampleClosest(-xEpsilonVec)) / TwoEpsilon;
	float yNormal = (SampleClosest(yEpsilonVec) - SampleClosest(-yEpsilonVec)) / TwoEpsilon;
	float zNormal = (SampleClosest(zEpsilonVec) - SampleClosest(-zEpsilonVec)) / TwoEpsilon;

	return Vec3(xNormal, yNormal, zNormal);
}
