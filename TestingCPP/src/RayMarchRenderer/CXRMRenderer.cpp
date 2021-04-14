#include "CXRMRenderer.h"

static const float DEFAULT_FAR_VIEW_DISTANCE = 100.0f;

//private

CXRayMarchInfo CXRMRenderer::RayMarchFromCam(const Vec3& rayDirection) const
{
	return _renderScene.RayMarchTo(_camera.position, rayDirection,
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
			float uv_x = (float)x / width,
				uv_y = (float)y / height;

			float camUV_x = uv_x -.5f, camUV_y = uv_y -.5f;

			Vec3 rayDirFromCam = _camera.GetRayDirection(camUV_x, camUV_y);

			//each pixel (which is UV :D)
			CXColor finalColor(0, 0, 0);

			CXRayMarchInfo rayMarchInfo = RayMarchFromCam(rayDirFromCam);

			if (rayMarchInfo.isHit)
			{
				/*finalColor.SetColor(rayMarchInfo.hitPoint.x, rayMarchInfo.hitPoint.y, rayMarchInfo.hitPoint.z);*/

				Vec3 normal = rayMarchInfo.rendObject_sharePtr->GetNormal(rayMarchInfo.hitPoint);

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
