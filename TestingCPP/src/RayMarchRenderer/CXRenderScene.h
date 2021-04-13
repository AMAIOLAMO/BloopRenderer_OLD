#pragma once

#include <vector>
#include "CXRayMarchInfo.h"
#include "RenderObjects/CXRenderObject.h"

/// <summary>
/// A renderable scene to pass into the Ray march renderer
/// </summary>
class CXRenderScene
{
private:
	std::vector<CXRenderObject> _rendObjects;

public:
	/// <summary>
	/// Creates an empty scene
	/// </summary>
	CXRenderScene();

	/// <summary>
	/// Receives the object and store it in as a render scene
	/// </summary>
	CXRenderScene(const std::vector<CXRenderObject>& rendObjects);

	/// <summary>
	/// Deep copies the whole scene
	/// </summary>
	CXRenderScene(const CXRenderScene& other);

	/// <summary>
	/// adds a new renderable object to the scene
	/// </summary>
	CXRenderScene& Add(const CXRenderObject& obj);

	CXRayMarchInfo RayMarch(Vec3 rayOrigin, Vec3 rayDirection,
		size_t maxMarchIteration,float minSurfaceDistance, float farViewDistance) const;

	/// <summary>
	/// Tries to get the closest distance from a specified from point to the entire scene
	/// (WILL OPTIMIZE WITH A CHUNK BASED DISTANCE MAP)
	/// </summary>
	bool TryGetClosestDistance(Vec3 fromPoint, float* const out_distance,
		CXRenderObject** out_renderObject_ptr) const;
	/*bool TryGetClosestDistance(Vec3 fromPoint, float* const out_distance,
		std::shared_ptr<CXRenderObject>* const out_renderObject_sharePtr) const;*/

	/// <summary>
	/// Get's the closest distance from the specified from Point to the entire scene
	/// (RETURNS NAN IF NO OBJECTS ON SCENE)
	/// (WILL OPTIMIZE WITH A CHUNK BASED DISTANCE MAP)
	/// </summary>
	float GetClosestDistance(Vec3 fromPoint) const;

	/// <summary>
	/// Get's the list of render objects (readonly)
	/// </summary>
	const std::vector<CXRenderObject>& GetRendObjects() const;
};
