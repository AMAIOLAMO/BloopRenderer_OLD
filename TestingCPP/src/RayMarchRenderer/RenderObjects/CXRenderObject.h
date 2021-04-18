#pragma once

#include <memory>

//#include "CXMaterial.h"
class CXMaterial;
#include "CXRenderBody.h"

/// <summary>
/// A renderable object to pass into the CXScene
/// </summary>
class CXRenderObject
{
private:
	const CXMaterial* _materialPtr;

public:
	//a shared ptr that points to a render body
	std::shared_ptr<CXRenderBody> renderBody_sharePtr;

public:
	/*CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr, const CXMaterial& _material);*/

	//CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr);

	CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr, const CXMaterial*& materialPtr);

	CXRenderObject(const CXRenderObject& other);

	const CXMaterial* GetMaterial() const;

	~CXRenderObject();
};