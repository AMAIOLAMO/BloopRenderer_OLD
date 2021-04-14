#include <random>
#include <memory>
#include <iostream>

#include "CxLib/Logger/Logger.h"
#include "CxLib/Math/CXVector.h"
#include "CxLib/BitMap/CXBitMap.h"
#include "CxLib/BitMap/CXColor.h"

#include "RayMarchRenderer/CXRMRenderer.h"
#include "RayMarchRenderer/RenderObjects/PrimitiveRenderObjects.h"
#include "RayMarchRenderer/CXRenderScene.h"
#include "RayMarchRenderer/CXCamera.h"


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

	//we use make shared here because we store stuff here as a pointer to be safe and easy to access
	//renderScene.Add(std::make_shared<CXSphereRenderObject>(Vec3(0, 1, 5), 1));

	CXRMRenderer renderer(renderScene, camera);

	CXBitMap renderedBitmap(1000, 1000);

	renderer.RenderToBitmap(renderedBitmap);

	renderedBitmap.ExportTo(TARGET_IMG_PATH);

	logger << "Finished rendering from the renderer" << Logger::endl;
}