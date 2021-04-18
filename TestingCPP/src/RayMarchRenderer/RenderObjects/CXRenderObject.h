#pragma once

#include <memory>

//#include "CXMaterial.h"
class CXMaterialBase;
#include "CXRenderBody.h"

/// <summary>
/// A renderable object to pass into the CXScene
/// </summary>
class CXRenderObject
{
private:
	const CXMaterialBase* _materialPtr;

public:
	//a shared ptr that points to a render body
	std::shared_ptr<CXRenderBody> renderBody_sharePtr;

public:
	/*CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr, const CXMaterial& _material);*/

	//CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr);

	CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr, const CXMaterialBase*& materialPtr);

	CXRenderObject(const CXRenderObject& other);

	const CXMaterialBase* GetMaterial() const;

	~CXRenderObject();
};