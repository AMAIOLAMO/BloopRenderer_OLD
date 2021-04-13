#include "CXRenderScene.h"

//instantiates the render scene with render objects
CXRenderScene::CXRenderScene() :
	_rendObjects() {}

//simply just real copies the render object
CXRenderScene::CXRenderScene(const std::vector<CXRenderObject>& _rendObjects) :
	_rendObjects(_rendObjects) {}

CXRenderScene::CXRenderScene(const CXRenderScene& other) :
	_rendObjects(other.GetRendObjects()) {}

CXRenderScene& CXRenderScene::Add(const CXRenderObject& Obj)
{
	_rendObjects.push_back(Obj);
	return *this; //for chaining methods together
}

//get's the list of the render objects but promise not to modify it :D
const std::vector<CXRenderObject>& CXRenderScene::GetRendObjects() const
{
	return _rendObjects;
}