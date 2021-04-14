#pragma once

#include "CXRenderObject.h"

class CXSphereRenderObject : public CXRenderObject
{
public:
	float radius;

public:
	CXSphereRenderObject(Vec3 _position, float _radius);

	float GetSurfDistance(const Vec3& fromPos) const override;
};