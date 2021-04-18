#include "CXRenderObject.h"

//#include "CXMaterial.h"

std::shared_ptr<CXRenderBody> renderBody_sharePtr;
const CXMaterialBase* _materialPtr;

CXRenderObject::CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr, const CXMaterialBase*& materialPtr) :
	renderBody_sharePtr(_renderBody_sharePtr), _materialPtr(materialPtr) {}

CXRenderObject::CXRenderObject(const CXRenderObject& other) :
	renderBody_sharePtr(other.renderBody_sharePtr), _materialPtr(other._materialPtr) {}

const CXMaterialBase* CXRenderObject::GetMaterial() const { return _materialPtr; }

CXRenderObject::~CXRenderObject() {}
