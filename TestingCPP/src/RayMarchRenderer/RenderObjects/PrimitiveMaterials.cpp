#include "PrimitiveMaterials.h"
#include "../../CxLib/ShaderUtils/CXShaderUtils.h"

CXPhongMaterial::CXPhongMaterial(const CXColor& base, const CXColor& ambient, const CXColor& specular, const float& specPower) :
	CXMaterial(base), ambientColor(ambient), specularColor(specular), specularPower(specPower) {}

CXColor CXPhongMaterial::OnPixel(const unsigned int& x, const unsigned int& y,
	const unsigned int& width,const unsigned int& height,
	const CXRenderScene* const& renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& camera) const
{
	static const float shadowRemoveAmount = .7f;
	static const Vec3 fakeLightDir_normalized = Vec3::GetNormalized(Vec3(-.3f, 1, -.3f));

	Vec3 normal = GET_REND_BODY(rayMarchInfo)->GetNormal(rayMarchInfo.hitPoint);

	Vec3 reflectVec = CXShaderUtils::Reflect(rayMarchInfo.hitPoint, normal);

	//normalize the vector
	reflectVec.Normalize();

	//this is for checking shadows
	CXRayMarchInfo rayMarchFromPointToLightInfo =
		renderScene_ptr->RayMarchTo(rayMarchInfo.hitPoint + fakeLightDir_normalized, fakeLightDir_normalized, camera);

	float diffuseIntensity = CXMath::Clamp01(fakeLightDir_normalized.Dot(normal));

	float specularIntensity = .0f;

	//has shadow then we make light intensity low
	if (rayMarchFromPointToLightInfo.isHit)
	{
		//we max it so we don't get Under 0
		diffuseIntensity = CXMath::LimitMin(diffuseIntensity -
			(shadowRemoveAmount * (1.0f - rayMarchFromPointToLightInfo.hitDistance)), .0f);
	}
	else // if not hit, then is in light
		specularIntensity = powf(CXMath::LimitMin(reflectVec.Dot(fakeLightDir_normalized), .0f), specularPower);

	CXColor finalColor(baseColor);

	finalColor *= diffuseIntensity;

	finalColor += ambientColor;

	finalColor += specularColor * specularIntensity;

	return finalColor;
}
