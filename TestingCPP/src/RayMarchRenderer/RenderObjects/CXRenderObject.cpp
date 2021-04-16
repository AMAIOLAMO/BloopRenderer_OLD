#include "CXRenderObject.h"

//CXRenderObject::CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr, const CXMaterial& _material) :
//	renderBody_sharePtr(_renderBody_sharePtr), material(_material) {}

CXRenderObject::CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr) :
	renderBody_sharePtr(_renderBody_sharePtr) {}

//CXRenderObject::CXRenderObject(const CXRenderObject& other) :
//	CXRenderObject(other.renderBody_sharePtr, other.material) {}

CXRenderObject::CXRenderObject(const CXRenderObject& other) :
	CXRenderObject(other.renderBody_sharePtr) {}

CXRenderObject::~CXRenderObject() {}

//CXRenderObject::CXRenderObject(const Vec3& _position, const CXColor& _baseColor) :
//	position(_position), baseColor(_baseColor), material_ptr(nullptr) {}
//
//CXRenderObject::CXRenderObject(const Vec3& _position, const CXColor& _baseColor,
//	CXMaterial*& _material_Ptr) :
//	position(_position), baseColor(_baseColor), material_ptr(_material_Ptr) {}
//
//CXRenderObject::CXRenderObject(const CXRenderObject& other) :
//	position(other.position), baseColor(other.baseColor), material_ptr(other.material_ptr) {}
//
//CXRenderObject::~CXRenderObject()
//{
//	//if ptr exists then delete
//	if (material_ptr)
//		delete material_ptr;
//}
//
//static const float Epsilon = 1e-3f;
//static const float TwoEpsilon = Epsilon * 2.0f;
//
//CXColor CXRenderObject::GetMaterialColor(const Vec3& pointOnSurface) const
//{
//	return baseColor;
//}
//
////stole from Gary (thx Gary :D)
//Vec3 CXRenderObject::GetNormal(const Vec3& pointOnSurface) const
//{
//	//a static so compiler won't create each time when we call this function
//	float centerDist = GetSurfDistance(pointOnSurface);
//
//	auto SampleClosest = [&](const Vec3& epsilonVec) // pass by reference
//	{ return GetSurfDistance(pointOnSurface + epsilonVec) - centerDist; };
//
//	Vec3 xEpsilonVec = Vec3(Epsilon, 0, 0);
//	Vec3 yEpsilonVec = Vec3(0, Epsilon, 0);
//	Vec3 zEpsilonVec = Vec3(0, 0, Epsilon);
//
//	float xNormal = (SampleClosest(xEpsilonVec) - SampleClosest(-xEpsilonVec)) / TwoEpsilon;
//	float yNormal = (SampleClosest(yEpsilonVec) - SampleClosest(-yEpsilonVec)) / TwoEpsilon;
//	float zNormal = (SampleClosest(zEpsilonVec) - SampleClosest(-zEpsilonVec)) / TwoEpsilon;
//
//	return Vec3(xNormal, yNormal, zNormal);
//}
