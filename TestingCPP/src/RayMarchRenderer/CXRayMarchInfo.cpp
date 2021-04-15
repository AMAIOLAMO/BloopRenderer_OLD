#include "CXRayMarchInfo.h"

CXRayMarchInfo::~CXRayMarchInfo()
{
	//we don't do anything here, the shared pointer helps manage it for us :D
}

CXRayMarchInfo::CXRayMarchInfo(const Vec3& _hitPoint, const unsigned int& _marchCount, const bool& _isHit, const float& _hitDistance,
	const std::shared_ptr<CXRenderObject>& _rendObject_sharePtr) :
	hitPoint(_hitPoint), marchCount(_marchCount), isHit(_isHit),
	hitDistance(_hitDistance), rendObject_sharePtr(_rendObject_sharePtr) {}

CXRayMarchInfo::CXRayMarchInfo(const CXRayMarchInfo& other) :
	hitPoint(other.hitPoint), isHit(other.isHit), marchCount(other.marchCount),
	hitDistance(other.hitDistance), rendObject_sharePtr(other.rendObject_sharePtr) {}
