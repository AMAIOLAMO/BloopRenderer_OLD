#include "CXRMRenderer.h"

CXRMRenderer::CXRMRenderer() :
	_renderScene(CXRenderScene()), _camera(CXCamera(Vec3(0, 1, 0), Vec3(Vec3::DV::forward))) {}

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
			//each pixel (which is UV :D) (test as a white first :D)
			CXColor finalColor = CXColor(1, 1, 1);

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
