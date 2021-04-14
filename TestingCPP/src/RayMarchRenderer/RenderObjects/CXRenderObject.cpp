#include "CXRenderObject.h"

CXRenderObject::CXRenderObject(Vec3 _position) :
	position(_position) {}

CXRenderObject::CXRenderObject(const CXRenderObject& other) :
	position(other.position) {}

//float CXRenderObject::GetSurfDistance(Vec3 fromPos) const
//{
//	const float SPHERE_SIZE = 1.0f;
//
//	//THIS IS A TEST! A TEST SPHERE
//	return (position - fromPos).GetLength() - SPHERE_SIZE;
//	//return 0.0f;
//}

static const float Epsilon = 1e-3f;
static const float TwoEpsilon = Epsilon * 2.0f;

//stole from Gary (thx Gary :D)
Vec3 CXRenderObject::GetNormal(const Vec3& pointOnSurface) const
{
	//REMEMBER HERE WE USE this BECAUSE WE ARE CALLING A VIRTUAL METHOD

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