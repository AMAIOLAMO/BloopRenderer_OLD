#include <random>
#include <memory>
#include <iostream>
#include <chrono>

#include "CxLib/Logger/Logger.h"
#include "CxLib/Math/CXVector.h"
#include "CxLib/BitMap/CXBitMap.h"
#include "CxLib/BitMap/CXColor.h"

#include "RayMarchRenderer/CXCamera.h"
#include "RayMarchRenderer/CXRMRenderer.h"
#include "RayMarchRenderer/CXRenderScene.h"
#include "RayMarchRenderer/RenderObjects/CXMaterial.h"
#include "RayMarchRenderer/RenderObjects/PrimitiveMaterials.h"
#include "RayMarchRenderer/RenderObjects/PrimitiveRenderObjects.h"


void DoRenderSimpleScene(Console&);

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

void DoRenderSimpleScene(Console& console)
{
	CXRenderScene* renderScene_ptr = new CXRenderScene;
	CXCamera camera(Vec3(0, 1, -1), FAR_VIEW_DISTANCE);

	const CXMaterialBase* pMatPtr = new CXPhongMaterial(CXColor(1.0f, .0f, .0f));
	const CXMaterialBase* plainMatPtr = new CXMaterial(CXColor(.0f, 1.0f, .0f));

	auto redSphere = CXRenderObject(std::make_shared<CXSphereRenderBody>(Vec3(0, 1, 5), 1.0f), pMatPtr);
	auto greenSphere = CXRenderObject(std::make_shared<CXSphereRenderBody>(Vec3(1, 1, 5), 1.0f), plainMatPtr);

	/* auto bluePlane = CXInfPlaneRenderBody(Vec3(0, 0, 0), CXColor(0, 0, 1)); */

	//we use make shared here because we store stuff here as a pointer to be safe and easy to access
	renderScene_ptr->Add(std::make_shared<CXRenderObject>(redSphere))
		.Add(std::make_shared<CXRenderObject>(greenSphere));

		/* .Add(std::make_shared<CXRenderObject>(bluePlane)); */

	CXRMRenderer renderer(renderScene_ptr, camera);

	// ----------------- START GENERATING ----------------- //

	console.ChangeConsoleColor(Console::BLUE);

	console.Log("Instantiated renderer :D");

	CXBitMap renderedBitmap(200, 100);

	console.Log("Instantiated bit map");
	console.Log("Rendering to bit map :D");

	renderer.RenderToBitmap(renderedBitmap);

	console.Log("Exporting to bit map :D");

	renderedBitmap.ExportTo(TARGET_IMG_PATH);

	console.ChangeConsoleColor(Console::GREEN);

	console.Log("-----------------------------------------------");

	console.Log("Rendered Result");

	console << "Render size: " << renderedBitmap.GetWidth() << " x " << renderedBitmap.GetHeight() << Console::endl;

	console.Log("Finished rendering from the renderer");
}
