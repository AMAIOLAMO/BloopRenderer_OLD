#pragma once

#include "../CxLib/Math/CXVector.h"
#include "RenderObjects/CXRenderObject.h"
#include <memory>

/// <summary>
/// This stores info of a ray hitting onto a render Object in the renderer
/// </summary>
struct CXRayMarchInfo
{
public:
	const Vec3 hitPoint;
	const bool isHit;
	const float hitDistance;
	const CXRenderObject* const renderObject_ptr;

	CXRayMarchInfo() = delete;

	~CXRayMarchInfo();

	/// <summary>
	/// IF YOU ARE SEEING THIS, YOU AREN'T MEANT TO CREATE THIS UNLESS YOU KNOW WHAT U ARE DOING :D
	/// </summary>
	CXRayMarchInfo(const Vec3& _hitPoint, bool _isHit, float _hitDistance,
		const CXRenderObject& _renderObject);

	/// <summary>
	/// Deep copies this ray hit info
	/// </summary>
	CXRayMarchInfo(const CXRayMarchInfo& other);
};