#include "CXRayMarchInfo.h"

CXRayMarchInfo::~CXRayMarchInfo()
{
	//if render object ptr still exists, then delete it :D to prevent mem leaks
	if(renderObject_ptr)
		delete renderObject_ptr;
}

CXRayMarchInfo::CXRayMarchInfo(const Vec3& _hitPoint, bool _isHit, float _hitDistance,
	const CXRenderObject& _renderObject) :
	hitPoint(_hitPoint), isHit(_isHit), hitDistance(_hitDistance), renderObject_ptr(&_renderObject) {}

CXRayMarchInfo::CXRayMarchInfo(const CXRayMarchInfo& other) :
	hitPoint(other.hitPoint), isHit(other.isHit),
	hitDistance(other.hitDistance), renderObject_ptr(other.renderObject_ptr) {}
