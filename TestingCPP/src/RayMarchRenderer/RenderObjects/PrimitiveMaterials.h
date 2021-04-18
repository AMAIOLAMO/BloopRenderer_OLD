#pragma once

#include "CXMaterial.h"

class CXPhongMaterial : public CXMaterial
{
public:
	CXColor ambientColor;
	CXColor specularColor;
	float specularPower;

public:
	CXPhongMaterial(const CXColor& base, const CXColor& ambient, const CXColor& specular, const float& specPower);

	__OVERRIDE_ON_PIXEL;
};
