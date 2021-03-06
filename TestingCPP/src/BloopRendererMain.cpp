#include <random>
#include <memory>
#include <iostream>
#include <chrono>

#include "CxLib/Math/CXVector.h"
#include "CxLib/BitMap/CXColor.h"
#include "CxLib/BitMap/CXBitMap.h"
#include "CxLib/Logger/CXConsole.h"

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

	DoRenderSimpleScene(mainConsole);

	std::cin.get();
}

//makes a shared render object
#define MK_SHARE_RENDOBJ(obj) std::make_shared<CXRenderObject>(obj)

void DoRenderSimpleScene(Console& console)
{
	auto renderScene_ptr = new CXRenderScene;
	const CXCamera camera(Vec3(0, 1, -5), FAR_VIEW_DISTANCE);

	const CXMaterialBase* pMatPtr = new CXPhongMaterial(CXColor(1, 0, 0), CXColor(.2f, 0, .1f), CXColor(1, 1, 1), 50.0f);
	const CXMaterialBase* plainMatPtr = new CXMaterial(CXColor(0, 1, 0));

	const CXMaterialBase* gMatPtr = new CXMaterial(CXColor(0, 0, 1));

	const CXMaterialBase* boxMat = new CXDiffuseMaterial(CXColor(1, 0, 0));

	const CXMaterialBase* reflectMat = new CXReflectiveMaterial(1);

	auto redSphere = CXRenderObject(std::make_shared<CXSphereRenderBody>(Vec3(0, 1, 5), 1.0f), pMatPtr);
	auto greenSphere = CXRenderObject(std::make_shared<CXSphereRenderBody>(Vec3(1, 1, 5), 1.0f), plainMatPtr);

	auto reflectSphere = CXRenderObject(std::make_shared<CXSphereRenderBody>(Vec3(-2, 1, 5), 1.0f), reflectMat);

	auto bluePlane = CXRenderObject(std::make_shared<CXInfPlaneRenderBody>(Vec3(0, 0, 0)), gMatPtr);

	auto redBox = CXRenderObject(std::make_shared<CXBoxRenderBody>(Vec3(-1, 3, 0), Vec3(.8f, .8f, .8f)), boxMat);

	//we use make shared here because we store stuff here as a pointer to be safe and easy to access
	renderScene_ptr->Add(MK_SHARE_RENDOBJ(redSphere))
		.Add(MK_SHARE_RENDOBJ(greenSphere))
		.Add(MK_SHARE_RENDOBJ(reflectSphere))
		.Add(MK_SHARE_RENDOBJ(redBox))
		.Add(MK_SHARE_RENDOBJ(bluePlane));

	CXRMRenderer renderer(renderScene_ptr, camera);

	// ----------------- START GENERATING ----------------- //

	Console::Log("Instantiated renderer :D");

	CXBitMap resultImage(160, 90);

	Console::Log("Instantiated bit map");

	Console::Log("Rendering to bit map :D");

	// ----------------- RENDER ----------------- //

	std::chrono::steady_clock clock;

	auto startClock = clock.now();

	renderer.RenderToBitmap(resultImage);

	auto endClock = clock.now();

	auto timeElapsed = static_cast<std::chrono::duration<double>>(endClock - startClock);

	console << "Total time of rendering: " << timeElapsed.count() << " seconds\n";

	// ----------------- EXPORT ----------------- //

	console.Log("Exporting to bit map :D");

	resultImage.ExportTo(TARGET_IMG_PATH);

	console.ChangeConsoleColor(Console::GREEN);

	Console::Log("-----------------------------------------------");

	Console::Log("Rendered Result");

	console << "Render size: " << resultImage.GetWidth() << " x " << resultImage.GetHeight() << '\n';

	Console::Log("Finished rendering from the renderer :D");
}
