#include "PrimitiveMaterials.h"
#include "../../CxLib/ShaderUtils/CXShaderUtils.h"

//will change later
static const float shadowRemoveAmount = .7f;
static const Vec3 fakeLightDir_normalized = Vec3::GetNormalized(Vec3(-.3f, 1, -.3f));

// ---------------- DIFFUSE MATERIAL ---------------- //

CXDiffuseMaterial::CXDiffuseMaterial(const CXColor& base) :
	CXMaterial(base) {}

CXColor CXDiffuseMaterial::OnPixel(const unsigned int& x, const unsigned int& y,
	const unsigned int& width, const unsigned int& height,
	const CXRenderScene* const& renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& camera) const
{
	Vec3 normal = GET_REND_BODY(rayMarchInfo)->GetNormal(rayMarchInfo.hitPoint);

	//this is for checking shadows
	/*CXRayMarchInfo rayMarchFromPointToLightInfo =
		renderScene_ptr->RayMarchTo(rayMarchInfo.hitPoint + fakeLightDir_normalized, fakeLightDir_normalized, camera);*/

	CXRayMarchInfo rayMarchFromPointToLightInfo =
		renderScene_ptr->RayMarchFromHitPoint(rayMarchInfo.hitPoint, fakeLightDir_normalized, camera);

	float diffuseIntensity = CXMath::LimitMin(fakeLightDir_normalized.Dot(normal), .0f);

	//has shadow then we make light intensity low
	if (rayMarchFromPointToLightInfo.isHit)
	{
		//we max it so we don't get Under 0
		diffuseIntensity = CXMath::LimitMin(diffuseIntensity -
			(shadowRemoveAmount * (1.0f - rayMarchFromPointToLightInfo.hitDistance)), .0f);
	}

	// ---------------- FINAL COLOR ---------------- //

	return baseColor * diffuseIntensity;
}

// ---------------- PHONG MATERIAL ---------------- //

CXPhongMaterial::CXPhongMaterial(const CXColor& base, const CXColor& ambient, const CXColor& specular, const float& specPower) :
	CXMaterial(base), ambientColor(ambient), specularColor(specular), specularPower(specPower) {}

CXColor CXPhongMaterial::OnPixel(const unsigned int& x, const unsigned int& y,
	const unsigned int& width,const unsigned int& height,
	const CXRenderScene* const& renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& camera) const
{
	Vec3 normal = GET_REND_BODY(rayMarchInfo)->GetNormal(rayMarchInfo.hitPoint);

	Vec3 reflectVec = CXShaderUtils::Reflect(rayMarchInfo.hitPoint, normal);

	//normalize the vector
	reflectVec.Normalize();

	//this is for checking shadows
	CXRayMarchInfo rayMarchFromPointToLightInfo =
		renderScene_ptr->RayMarchFromHitPoint(rayMarchInfo.hitPoint, fakeLightDir_normalized, camera);
		//renderScene_ptr->RayMarchTo(rayMarchInfo.hitPoint + fakeLightDir_normalized, fakeLightDir_normalized, camera);

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

	// ---------------- FINAL COLOR ---------------- //

	CXColor finalColor(baseColor);

	finalColor *= diffuseIntensity;

	finalColor += ambientColor;

	finalColor += specularColor * specularIntensity;

	return finalColor;
}

// ---------------- REFLECT MATERIAL ---------------- //

CXReflectiveMaterial::CXReflectiveMaterial(const unsigned int& _maxReflectCount) :
	maxReflectCount(_maxReflectCount) {}

CXColor CXReflectiveMaterial::OnPixel(const unsigned int& x, const unsigned int& y,
	const unsigned int& width, const unsigned int& height,
	const CXRenderScene* const& renderScene_ptr, const CXRayMarchInfo& rayMarchInfo, const CXCamera& camera) const
{
	Vec3 normal = GET_REND_BODY(rayMarchInfo)->GetNormal(rayMarchInfo.hitPoint);
	Vec3 reflectVec = Vec3::GetNormalized(CXShaderUtils::Reflect(rayMarchInfo.hitPoint, normal));

	Vec3 lastHitPoint(rayMarchInfo.hitPoint);

	CXColor finalColor(0, 0, 0);

	//loop in amount of how much we can reflect
	for (unsigned int i = 0; i < maxReflectCount; i++)
	{
		//we start reflecting
		CXRayMarchInfo reflectOnRayMarchInfo = renderScene_ptr->RayMarchFromHitPoint(lastHitPoint, reflectVec, camera);

		if (!reflectOnRayMarchInfo.isHit)
			break;

		//if we got a Hit!
		//finalColor += CXColor::FromGreyScale(.2f);
		
		finalColor += reflectOnRayMarchInfo.rendObject_sharePtr->GetMaterial()->
			OnPixel(x, y, width, height, renderScene_ptr, reflectOnRayMarchInfo, camera);

		lastHitPoint = reflectOnRayMarchInfo.hitPoint;

		normal = GET_REND_BODY(reflectOnRayMarchInfo)->GetNormal(lastHitPoint);
		reflectVec = Vec3::GetNormalized(CXShaderUtils::Reflect(lastHitPoint, normal));
	}

	return finalColor;
}