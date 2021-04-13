#include "CXRMRenderer.h"

static const float DEFAULT_FAR_VIEW_DISTANCE = 100.0f;

//private

CXRayMarchInfo CXRMRenderer::RayMarchFromCam(Vec3 rayDirection) const
{
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
			CXColor finalColor(0, 0, 0);

			CXRayMarchInfo rayMarchInfo = RayMarchFromCam(rayDirFromCam);

			//float distance = RayMarchFromCam(rayDirFromCam);

			//Vec3 rayPoint = _camera.position + rayDirFromCam * distance;

			//float greyScale = 1.0f - rayMarchInfo.hitDistance / 6.0f;

			if (rayMarchInfo.isHit)
			{
				Vec3 normal = rayMarchInfo.renderObject->GetNormal(rayMarchInfo.hitPoint);

				finalColor.SetColor(normal.x, normal.y, normal.z);
			}

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
