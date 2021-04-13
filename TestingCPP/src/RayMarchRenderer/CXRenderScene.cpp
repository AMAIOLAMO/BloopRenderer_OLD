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

bool CXRenderScene::TryGetClosestDistance(Vec3 fromPoint, float* out_distance) const
{
	if (_rendObjects.size() == 0)
	{
		*out_distance = NAN;
		return false;
	}
	if (_rendObjects.size() == 1)
	{
		*out_distance = _rendObjects[0].GetSurfDistance(fromPoint);
		return true;
	}

	//else there are more than 1 rendering objects :D (at least 2)

	float minDist = _rendObjects[0].GetSurfDistance(fromPoint);

	//from the second (because we used the first one)
	for (size_t i = 1; i < _rendObjects.size(); i++)
	{
		float currentDist = _rendObjects[i].GetSurfDistance(fromPoint);

		//if current distance is smaller than the min distance, update :D
		if (minDist > currentDist)
			minDist = currentDist;
	}

	*out_distance = minDist;

	return true;
}

float CXRenderScene::GetClosestDistance(Vec3 fromPoint) const
{
	float outDist;
	TryGetClosestDistance(fromPoint, &outDist);

	return outDist;
}

//get's the list of the render objects but promise not to modify it :D
const std::vector<CXRenderObject>& CXRenderScene::GetRendObjects() const
{
	return _rendObjects;
}