#pragma once

#include "CXMaterial.h"

class CXDiffuseMaterial : public CXMaterial
{
public:
	CXDiffuseMaterial(const CXColor& base);

	__OVERRIDE_ON_PIXEL;
};



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
