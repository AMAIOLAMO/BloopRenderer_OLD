#pragma once

#include "../CXRenderScene.h"
#include "../../CxLib/BitMap/CXColor.h"


/// <summary>
/// A material stores a list of methods to calculate how the light is effected on this material
/// </summary>
class CXMaterial
{
public:
	virtual CXColor OnPixel(const unsigned int& x, const unsigned int& y,
		const unsigned int& width, const unsigned int& height, const CXRenderScene* const & renderScene_ptr) const;
};