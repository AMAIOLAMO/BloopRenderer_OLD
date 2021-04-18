#pragma once

#include "../CXCamera.h"
#include "../CXRenderScene.h"
#include "../../CxLib/Math/CXMath.h"
#include "../../CxLib/BitMap/CXColor.h"

//Used only in MATERIAL DEFENITIONS!
#define __OVERRIDE_ON_PIXEL virtual CXColor OnPixel(const unsigned int& x, const unsigned int& y,\
		const unsigned int& width, const unsigned int& height,\
		const CXRenderScene* const& renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& cam) const override

/// <summary>
/// the base of a material
/// </summary>
class CXMaterialBase
{
public:
	/// <summary>
	/// This is called when the current rendering pixel is on a object
	/// </summary>
	virtual CXColor OnPixel(const unsigned int& x, const unsigned int& y,
		const unsigned int& width, const unsigned int& height,
		const CXRenderScene* const & renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& camera) const;
};

/// <summary>
/// a material that has a base color
/// </summary>
class CXMaterial : public CXMaterialBase
{
public:
	CXColor baseColor;

public:
	CXMaterial(const CXColor& color);

	__OVERRIDE_ON_PIXEL;
};