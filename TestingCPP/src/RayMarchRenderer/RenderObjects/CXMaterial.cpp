#include "CXMaterial.h"

CXColor CXMaterial::OnPixel(const unsigned int& x, const unsigned int& y,
	const unsigned int& width, const unsigned int& height, const CXRenderScene& renderScene) const
{
	return CXColor(1.0f, 1.0f, 1.0f);
}
