#pragma once

#include <vector>
#include "CXRenderObject.h"

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

	/// <summary>
	/// Get's the list of render objects (readonly)
	/// </summary>
	const std::vector<CXRenderObject>& GetRendObjects() const;
};