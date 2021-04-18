#include "CXMaterial.h"

CXColor CXMaterialBase::OnPixel(const unsigned int& x, const unsigned int& y,
	const unsigned int& width, const unsigned int& height,
	const CXRenderScene* const & renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& cam) const
{
	return CXColor(1.0f, 1.0f, 1.0f);
}

// ---------------- MATERIAL ---------------- //

CXMaterial::CXMaterial(const CXColor& color) :
	baseColor(color) {}

CXColor CXMaterial::OnPixel(const unsigned int& x, const unsigned int& y,
	const unsigned int& width, const unsigned int& height,
	const CXRenderScene* const& renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& cam) const
{
	return baseColor;
}