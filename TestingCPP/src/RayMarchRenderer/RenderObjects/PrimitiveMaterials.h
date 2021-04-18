#pragma once

#include "CXMaterial.h"

class CXPhongMaterial : public CXMaterial
{
	CXColor OnPixel(const unsigned int& x, const unsigned int& y,
		const unsigned int& width, const unsigned int& height,
		const CXRenderScene* const& renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& cam) const override;
};
