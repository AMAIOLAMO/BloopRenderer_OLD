#include <iostream>
#include <random>

#include "CxLib/Logger/Logger.h"
#include "CxLib/Math/CXVector.h"
#include "CxLib/BitMap/CXBitMap.h"
#include "CxLib/BitMap/CXColor.h"

#include "RayMarchRenderer/CXRMRenderer.h"
#include "RayMarchRenderer/CXRenderScene.h"
#include "RayMarchRenderer/CXCamera.h"

void DoGenerateRandomBitMap(const Logger&);

void DoRenderSimpleScene(const Logger&);

const char* TARGET_IMG_PATH = "C:/Users/alienware/Desktop/myImage.bmp";

const float FAR_VIEW_DISTANCE = 100.0f;

int main()
{
	Logger myLogger;

	DoRenderSimpleScene(myLogger);

	std::cin.get();
}

void DoRenderSimpleScene(const Logger& logger)
{
	CXRenderScene renderScene;
	CXCamera camera(Vec3(0, 1, 0), FAR_VIEW_DISTANCE); // we don't care about where it is looking at rn it's fixed :D

	logger.Log(renderScene.GetRendObjects().size());

	renderScene.Add(CXRenderObject(Vec3(0, 1, 5)));

	//renderScene.EmplaceAdd(0, 1, 5);
	//renderScene.Add(CXRenderObject(Vec3(0, 1, 5)));

	CXRMRenderer renderer(renderScene, camera);

	CXBitMap renderedBitmap(500, 500);

	renderer.RenderToBitmap(renderedBitmap);

	renderedBitmap.ExportTo(TARGET_IMG_PATH);

	logger.Log("Finished rendering from the renderer");
}

void DoGenerateRandomBitMap(const Logger& logger)
{
	std::random_device rseed;
	std::mt19937 rgen(rseed()); // mersenne_twister
	std::uniform_int_distribution<int> idist(0, 255);

	const int width = 1200;
	const int height = 1900;

	CXBitMap myImage(width, height);

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			myImage.SetColor(CXColor(idist(rgen) / 255.0f,
				idist(rgen) / 255.0f,
				idist(rgen) / 255.0f), x, y);
		}
	}

	myImage.ExportTo(TARGET_IMG_PATH);

	logger.Log("Finished Generating random bit map");
}