#pragma once

#include <memory>

#include "../CxLib/Math/CXVector.h"
#include "RenderObjects/CXRenderObject.h"

/// <summary>
/// This stores info of a ray hitting onto a render Object in the renderer
/// </summary>
struct CXRayMarchInfo
{
public:
	const Vec3 hitPoint;
	const bool isHit;
	const float hitDistance;
	const unsigned int marchCount;
	const std::shared_ptr<CXRenderObject> rendObject_sharePtr;

	CXRayMarchInfo() = delete;

	~CXRayMarchInfo();

	/// <summary>
	/// IF YOU ARE SEEING THIS, YOU AREN'T MEANT TO CREATE THIS UNLESS YOU KNOW WHAT U ARE DOING :D
	/// </summary>
	CXRayMarchInfo(const Vec3& _hitPoint, const unsigned int& _marchCount, const bool& _isHit, const float& _hitDistance,
		const std::shared_ptr<CXRenderObject>& _rendObject_sharePtr);

	/// <summary>
	/// Deep copies this ray hit info
	/// </summary>
	CXRayMarchInfo(const CXRayMarchInfo& other);
};