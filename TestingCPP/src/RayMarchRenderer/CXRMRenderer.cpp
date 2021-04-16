#include "CXRMRenderer.h"

static const float DEFAULT_FAR_VIEW_DISTANCE = 100.0f;

//private

CXRayMarchInfo CXRMRenderer::RayMarchFrom(const Vec3& rayOrigin, const Vec3& rayDirection) const
{
	return _renderScene_ptr->RayMarchTo(rayOrigin, rayDirection,
		maxMarchingIteration, minSurfaceDistance, _camera.farViewDistance);
}

CXRayMarchInfo CXRMRenderer::RayMarchFromCam(const Vec3& rayDirection) const
{
	return RayMarchFrom(_camera.position, rayDirection);
}

//public

CXRMRenderer::CXRMRenderer(CXRenderScene*& renderScene_ptr, const CXCamera& camera) :
	_renderScene_ptr(renderScene_ptr), _camera(camera) {}

CXRMRenderer::~CXRMRenderer()
{
	if (_renderScene_ptr)
		delete _renderScene_ptr;
}

const CXRenderScene*& CXRMRenderer::GetRenderScene_Ptr()
{
	return _renderScene_ptr;
}

void CXRMRenderer::RenderToBitmap(CXBitMap& targetBitmap) const
{
	int width = targetBitmap.GetWidth(),
		height = targetBitmap.GetHeight();

	//loop in the whole img (this as the UV of the camera)
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			CXColor finalPixel = OnPixelLoop(x, y, width, height);

			targetBitmap.SetColor(finalPixel, x, y);
		}
	}
}

CXColor CXRMRenderer::OnPixelLoop(int x, int y, int width, int height) const
{
	float resDiv = CXMath::Max(static_cast<float>(width), static_cast<float>(height));

	float uv_x = (float)x / resDiv,
		uv_y = (float)y / resDiv;

	float centerX = (static_cast<float>(width) / resDiv) / 2.0f,
		centerY = (static_cast<float>(height) / resDiv) / 2.0f;

	float camUV_x = uv_x - centerX, camUV_y = uv_y - centerY;

	static const float shadowRemoveAmount = .7f;

	static const Vec3 fakeLightDir_normalized = Vec3::GetNormalized(Vec3(-.3f, 1, -.3f));

	Vec3 rayDirFromCam = _camera.GetRayDirection(camUV_x, camUV_y);

	//each pixel (which is UV :D)
	CXColor finalColor(0, 0, 0);

	CXRayMarchInfo rayMarchFromCamInfo = RayMarchFromCam(rayDirFromCam);


	if (rayMarchFromCamInfo.isHit)
	{
#if 0
		finalColor = rayMarchFromCamInfo.rendObject_sharePtr->material.OnPixel(x, y, width, height, _renderScene_ptr);

		//if ptr exists
		/*if (rayMarchFromCamInfo.rendObject_sharePtr-)
		{
			finalColor = rayMarchFromCamInfo.rendObject_sharePtr->
				material_ptr->OnPixel(x, y, width, height, _renderScene);
		}*/
		
#endif
#if 1
		Vec3 normal = rayMarchFromCamInfo.rendObject_sharePtr->renderBody_sharePtr->GetNormal(rayMarchFromCamInfo.hitPoint);

		CXColor materialColor = CXColor(1, 1, 1);
			//rayMarchFromCamInfo.rendObject_sharePtr->renderBody_sharePtr->GetMaterialColor(rayMarchFromCamInfo.hitPoint);

		//this is for checking shadows
		CXRayMarchInfo rayMarchFromPointToLightInfo =
			RayMarchFrom(rayMarchFromCamInfo.hitPoint + fakeLightDir_normalized, fakeLightDir_normalized);

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

		finalColor = materialColor * lightIntensity;
#endif
	}
	else
	{
		//make not completely black
		static CXColor tempBackground = CXColor::FromGreyScale(0.2f);

		finalColor = tempBackground;
	}

	return finalColor;
}

CXBitMap* CXRMRenderer::RenderToBitmap(int width, int height) const
{
	CXBitMap* resultBitmap = new CXBitMap(width, height);

	RenderToBitmap(*resultBitmap);

	return resultBitmap;
}
