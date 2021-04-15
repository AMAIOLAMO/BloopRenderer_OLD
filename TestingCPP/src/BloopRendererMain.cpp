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
#include "RayMarchRenderer/RenderObjects/CXMaterial.h"


void DoRenderSimpleScene(const Console&);

const char* TARGET_IMG_PATH = "C:/Users/alienware/Desktop/myImage.bmp";

const float FAR_VIEW_DISTANCE = 100.0f;

int main()
{
	Console mainConsole;

	std::chrono::steady_clock clock;

	auto startClock = clock.now();

	DoRenderSimpleScene(mainConsole);

	auto endClock = clock.now();

	auto timeElapsed = static_cast<std::chrono::duration<double>>(endClock - startClock);

	mainConsole << "Total time of rendering: " << timeElapsed.count() << " seconds" << Console::endl;

	std::cin.get();
}

void DoRenderSimpleScene(const Console& console)
{
	CXRenderScene renderScene;
	CXCamera camera(Vec3(0, 1, -1), FAR_VIEW_DISTANCE); // we don't care about where it is looking at rn it's fixed :D

	CXMaterial* matPtr = new CXMaterial();

	auto redSphere = CXSphereRenderObject(Vec3(-1, 1, 5), CXColor(1, 0, 0), matPtr, 1);
	auto greenSphere = CXSphereRenderObject(Vec3(1, 1, 5), CXColor(0, 1, 0), 1);
	auto bluePlane = CXInfPlaneRenderObject(Vec3(0, 0, 0), CXColor(0, 0, 1));

	//redSphere.material_sharePtr = std::make_shared<CXMaterial>();

	//we use make shared here because we store stuff here as a pointer to be safe and easy to access
	renderScene.Add(std::make_shared<CXSphereRenderObject>(redSphere))
		.Add(std::make_shared<CXSphereRenderObject>(greenSphere))
		.Add(std::make_shared<CXInfPlaneRenderObject>(bluePlane));

	CXRMRenderer renderer(renderScene, camera);

	console.Log("Instantiated renderer :D");

	CXBitMap renderedBitmap(200, 100);

	console.Log("Instantiated bit map");
	console.Log("Rendering to bit map :D");

	renderer.RenderToBitmap(renderedBitmap);

	console.Log("Exporting to bit map :D");

	renderedBitmap.ExportTo(TARGET_IMG_PATH);

	console.Log("-----------------------------------------------");

	console.Log("Rendered Result");

	console << "Render size: " << renderedBitmap.GetWidth() << " x " << renderedBitmap.GetHeight() << Console::endl;

	console.Log("Finished rendering from the renderer");
}
