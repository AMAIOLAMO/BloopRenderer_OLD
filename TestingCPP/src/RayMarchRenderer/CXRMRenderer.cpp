#include "CXRMRenderer.h"

static const float DEFAULT_FAR_VIEW_DISTANCE = 100.0f;

//private

CXRayMarchInfo CXRMRenderer::RayMarchFrom(const Vec3& rayOrigin, const Vec3& rayDirection) const
{
	return _renderScene.RayMarchTo(rayOrigin, rayDirection,
		maxMarchingIteration, minSurfaceDistance, _camera.farViewDistance);
}

CXRayMarchInfo CXRMRenderer::RayMarchFromCam(const Vec3& rayDirection) const
{
	return RayMarchFrom(_camera.position, rayDirection);
}

//public

CXRMRenderer::CXRMRenderer() :
	_renderScene(CXRenderScene()), _camera(CXCamera(Vec3(0, 1, 0), DEFAULT_FAR_VIEW_DISTANCE)) {}

CXRMRenderer::CXRMRenderer(const CXRenderScene& renderScene, const CXCamera& camera) :
	_renderScene(renderScene), _camera(camera) {}

CXRMRenderer::~CXRMRenderer() {}

const CXRenderScene& CXRMRenderer::GetRenderScene() const
{
	return _renderScene;
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

//this is where you write the shader
CXColor CXRMRenderer::OnPixelLoop(int x, int y, int width, int height) const
{
	float uv_x = (float)x / width,
		uv_y = (float)y / height;

	float camUV_x = uv_x - .5f, camUV_y = uv_y - .5f;

	static const float shadowRemoveAmount = .7f;

	static const Vec3 fakeLightDir_normalized = Vec3::GetNormalized(Vec3(-.3f, 1, -.3f));

	Vec3 rayDirFromCam = _camera.GetRayDirection(camUV_x, camUV_y);

	//each pixel (which is UV :D)
	CXColor finalColor(0, 0, 0);

	CXRayMarchInfo rayMarchFromCamInfo = RayMarchFromCam(rayDirFromCam);

	if (rayMarchFromCamInfo.isHit)
	{
		Vec3 normal = rayMarchFromCamInfo.rendObject_sharePtr->GetNormal(rayMarchFromCamInfo.hitPoint);

		CXColor materialColor =
			rayMarchFromCamInfo.rendObject_sharePtr->GetMaterialColor(rayMarchFromCamInfo.hitPoint);

		//this is for checking shadows
		CXRayMarchInfo rayMarchFromPointInfo =
			RayMarchFrom(rayMarchFromCamInfo.hitPoint + fakeLightDir_normalized, fakeLightDir_normalized);

		//the light grey scale (between 0 and 1)
		float lightIntensity = CXMath::Clamp01(Vec3::Dot(fakeLightDir_normalized, normal));

		//has shadow
		if (rayMarchFromPointInfo.isHit)
		{
			//then we remove from the light :D
			//we limit at max of 1 so when it's closer to the ball it's more darker

			//this will go over 1
			//grayScale = rayMarchFromPointInfo.hitDistance;

			//grayScale -=  1.0f - (std::min(rayMarchFromPointInfo.hitDistance, 2.0f) / 2.0f);
		}

		finalColor = materialColor;
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
