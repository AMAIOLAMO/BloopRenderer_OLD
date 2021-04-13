#include "CXRayMarchInfo.h"

CXRayMarchInfo::CXRayMarchInfo(const Vec3& _hitPoint, bool _isHit, float _hitDistance,
	const CXRenderObject& _renderObject) :
	hitPoint(_hitPoint), isHit(_isHit), hitDistance(_hitDistance), renderObject(&_renderObject) {}

CXRayMarchInfo::CXRayMarchInfo(const CXRayMarchInfo& other) :
	hitPoint(other.hitPoint), isHit(other.isHit),
	hitDistance(other.hitDistance), renderObject(other.renderObject) {}
