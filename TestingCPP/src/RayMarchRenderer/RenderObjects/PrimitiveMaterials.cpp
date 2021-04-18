#include "PrimitiveMaterials.h"

CXColor CXPhongMaterial::OnPixel(const unsigned int& x, const unsigned int& y,
	const unsigned int& width,const unsigned int& height,
	const CXRenderScene* const& renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& cam) const
{
	static const float shadowRemoveAmount = .7f;
	static const Vec3 fakeLightDir_normalized = Vec3::GetNormalized(Vec3(-.3f, 1, -.3f));

	static const Vec3 normal = rayMarchInfo.rendObject_sharePtr->renderBody_sharePtr->GetNormal(rayMarchInfo.hitPoint);

	CXColor materialColor = CXColor(1, 1, 1);

	//this is for checking shadows
	CXRayMarchInfo rayMarchFromPointToLightInfo =
		renderScene_ptr->RayMarchTo(rayMarchInfo.hitPoint + fakeLightDir_normalized, fakeLightDir_normalized, cam);

	float lightIntensity;

	lightIntensity = CXMath::Clamp01(Vec3::Dot(fakeLightDir_normalized, normal));

	//has shadow then we make light intensity low
	if (rayMarchFromPointToLightInfo.isHit)
	{
		//we max it so we don't get Under 0
		lightIntensity = CXMath::LimitMin(lightIntensity -
			(shadowRemoveAmount * (1.0f - rayMarchFromPointToLightInfo.hitDistance)),
			0.0f);
	}

	return materialColor * lightIntensity;
}
