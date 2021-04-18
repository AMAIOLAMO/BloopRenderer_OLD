#include "CXRenderObject.h"

//#include "CXMaterial.h"

std::shared_ptr<CXRenderBody> renderBody_sharePtr;
const CXMaterial* _materialPtr;

//CXRenderObject::CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr, const CXMaterial& _material) :
//	renderBody_sharePtr(_renderBody_sharePtr), material(_material) {}

//CXRenderObject::CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr) :
//	renderBody_sharePtr(_renderBody_sharePtr) {}

CXRenderObject::CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr, const CXMaterial*& materialPtr) :
	renderBody_sharePtr(_renderBody_sharePtr), _materialPtr(materialPtr) {}

//CXRenderObject::CXRenderObject(const CXRenderObject& other) :
//	CXRenderObject(other.renderBody_sharePtr, other.material) {}

CXRenderObject::CXRenderObject(const CXRenderObject& other) :
	renderBody_sharePtr(other.renderBody_sharePtr), _materialPtr(other._materialPtr) {}
	//CXRenderObject(other.renderBody_sharePtr, other._materialPtr) {}

const CXMaterial* CXRenderObject::GetMaterial() const { return _materialPtr; }

CXRenderObject::~CXRenderObject() {}
