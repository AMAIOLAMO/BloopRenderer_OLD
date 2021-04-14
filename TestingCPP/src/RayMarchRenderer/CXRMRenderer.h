#pragma once
#include "CXRenderScene.h"
#include "../CxLib/BitMap/CXBitMap.h"
#include "CXCamera.h"


//This is where receives a scene and ray marches

/// <summary>
/// A simple ray march renderer made by CXRedix :D
/// </summary>
class CXRMRenderer
{
private:
	CXRenderScene _renderScene;
	CXCamera _camera;

public:
	unsigned int maxMarchingIteration = 100; //the max iterations a ray marching renderer should iterate
	float minSurfaceDistance = .01f; //the minimum distance for the ray marching sphere to be :D

private:
	CXRayMarchInfo RayMarchFromCam(const Vec3& rayDirection) const;

public:
	/// <summary>
	/// creates a very empty scene to render
	/// </summary>
	CXRMRenderer();

	/// <summary>
	/// uses the target render scene to render
	/// </summary>
	CXRMRenderer(const CXRenderScene& renderScene, const CXCamera& camera);

	/// <summary>
	/// A renderer IS NOT MEANT TO BE COPIED
	/// </summary>
	CXRMRenderer(const CXRMRenderer& other) = delete;

	~CXRMRenderer();

	/// <summary>
	/// Get's the render scene (readonly)
	/// </summary>
	const CXRenderScene& GetRenderScene() const;

	/// <summary>
	/// Renders the scene to the target bitmap (this function only modifies the input)
	/// </summary>
	void RenderToBitmap(CXBitMap& targetBitmap) const;

	/// <summary>
	/// Renders the scene to a new bitmap (THIS IS HEAP ALLOCATED, PLS DELETE IT YOURSELF)
	/// </summary>
	CXBitMap* RenderToBitmap(int width, int height) const;
};