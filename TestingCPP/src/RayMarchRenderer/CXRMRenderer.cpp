#include "CXRMRenderer.h"

static const float DEFAULT_FAR_VIEW_DISTANCE = 100.0f;

//private

CXRayMarchInfo CXRMRenderer::RayMarchFromCam(Vec3 rayDirection) const
{
	//float distanceFromOriginMarched = .0f;

	//for (size_t i = 0; i < maxMarchingIteration; i++)
	//{
	//	Vec3 marchedPoint = _camera.position + rayDir * distanceFromOriginMarched;

	//	float closestSceneDistanceFromMarchPoint = _renderScene.GetClosestDistance(marchedPoint);

	//	//add to the distance from origin marched :>
	//	distanceFromOriginMarched += closestSceneDistanceFromMarchPoint;

	//	//if marching circle's Radius is smaller than the min surface distance or is larger than the far view distance
	//	if (distanceFromOriginMarched < minSurfaceDistance ||
	//		distanceFromOriginMarched > _camera.farViewDistance) break;
	//}

	//return distanceFromOriginMarched;

	return _renderScene.RayMarch(_camera.position, rayDirection,
		maxMarchingIteration, minSurfaceDistance, _camera.farViewDistance);
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
			float uv_x = -.5f + (float)x / width,
				uv_y = -.5f + (float)y / height;

			Vec3 rayDirFromCam = _camera.GetRayDirection(uv_x, uv_y);

			//each pixel (which is UV :D)
			CXColor finalColor;

			CXRayMarchInfo rayMarchInfo = RayMarchFromCam(rayDirFromCam);

			//float distance = RayMarchFromCam(rayDirFromCam);

			//Vec3 rayPoint = _camera.position + rayDirFromCam * distance;

			float greyScale = 1.0f - rayMarchInfo.hitDistance / 6.0f;

			finalColor = CXColor::FromGreyScale(greyScale);

			targetBitmap.SetColor(finalColor, x, y);
		}
	}
}

CXBitMap* CXRMRenderer::RenderToBitmap(int width, int height) const
{
	CXBitMap* resultBitmap = new CXBitMap(width, height);

	RenderToBitmap(*resultBitmap);

	return resultBitmap;
}
