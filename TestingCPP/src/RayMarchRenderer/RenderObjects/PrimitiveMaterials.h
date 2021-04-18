#pragma once

#include "CXMaterial.h"

class CXPhongMaterial : public CXMaterial
{
public:
	CXPhongMaterial(const CXColor& color);

	__OVERRIDE_ON_PIXEL;

	/*CXColor OnPixel(const unsigned int& x, const unsigned int& y,
		const unsigned int& width, const unsigned int& height,
		const CXRenderScene* const& renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& cam) const override;*/
};
