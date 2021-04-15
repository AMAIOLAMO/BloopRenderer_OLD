#include <random>
#include <memory>
#include <iostream>
#include <chrono>

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

	std::chrono::steady_clock clock;

	auto startClock = clock.now();

	DoRenderSimpleScene(myLogger);

	auto endClock = clock.now();

	auto timeElapsed = static_cast<std::chrono::duration<double>>(endClock - startClock);

	myLogger << "Total time of rendering: " << timeElapsed.count() << " seconds" << Logger::endl;

	std::cin.get();
}

void DoRenderSimpleScene(const Logger& logger)
{
	CXRenderScene renderScene;
	CXCamera camera(Vec3(0, 1, -1), FAR_VIEW_DISTANCE); // we don't care about where it is looking at rn it's fixed :D

	auto redSphere = CXSphereRenderObject(Vec3(-1, 1, 5), CXColor(1, 0, 0), 1);
	auto greenSphere = CXSphereRenderObject(Vec3(1, 1, 5), CXColor(0, 1, 0), 1);
	auto bluePlane = CXInfPlaneRenderObject(Vec3(0, 0, 0), CXColor(0, 0, 1));

	//we use make shared here because we store stuff here as a pointer to be safe and easy to access
	renderScene.Add(std::make_shared<CXSphereRenderObject>(redSphere))
		.Add(std::make_shared<CXSphereRenderObject>(greenSphere))
		.Add(std::make_shared<CXInfPlaneRenderObject>(bluePlane));

	CXRMRenderer renderer(renderScene, camera);

	logger.Log("Instantiated renderer :D");

	CXBitMap renderedBitmap(1000, 1000);

	logger.Log("Instantiated bit map");
	logger.Log("Rendering to bit map :D");

	renderer.RenderToBitmap(renderedBitmap);

	logger.Log("Exporting to bit map :D");

	renderedBitmap.ExportTo(TARGET_IMG_PATH);

	logger.Log("Finished rendering from the renderer");
}
