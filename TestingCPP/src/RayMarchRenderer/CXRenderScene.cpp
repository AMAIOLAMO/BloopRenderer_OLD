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

CXRayMarchInfo CXRenderScene::RayMarch(Vec3 rayOrigin, Vec3 rayDirection,
	size_t maxMarchIteration, float minSurfaceDistance, float farViewDistance) const
{
	float distanceFromOriginMarched = .0f;

	bool isHit = false;

	Vec3 targetHitPoint(0, 0, 0);

	CXRenderObject* targetRenderObject_ptr = nullptr;

	for (size_t i = 0; i < maxMarchIteration; i++)
	{
		targetHitPoint = rayOrigin + rayDirection * distanceFromOriginMarched;

		float closestSurfDistInSceneFromMarchedPoint;

		//imagine we draw a circle to the closest distance if didn't get any closest distance.... then no object :D
		if (!TryGetClosestDistance(targetHitPoint, &closestSurfDistInSceneFromMarchedPoint, &targetRenderObject_ptr))
			continue;

		//else we got a distance with a marched point and the target render object

		//float closestSurfDistInSceneFromMarchedPoint = GetClosestDistance(pointMarchedTo);

		distanceFromOriginMarched += closestSurfDistInSceneFromMarchedPoint;

		if (closestSurfDistInSceneFromMarchedPoint < minSurfaceDistance) //is hit :D (raymarch circle so small)
		{
			isHit = true;
			//targetHitPoint = pointMarchedTo;
			break;
		}
		//else
		if (distanceFromOriginMarched > farViewDistance) //bruh not hit??? :< shoot too far
			break;
	}

	return CXRayMarchInfo(targetHitPoint, isHit, distanceFromOriginMarched, *targetRenderObject_ptr);
}

bool CXRenderScene::TryGetClosestDistance(Vec3 fromPoint,
	float* const out_distance, CXRenderObject** out_renderObject_ptr) const
{
	if (_rendObjects.size() == 0)
	{
		*out_distance = NAN;
		return false;
	}
	if (_rendObjects.size() == 1)
	{
		*out_distance = _rendObjects[0].GetSurfDistance(fromPoint);

		//change PTR!! NOT CONTENT
		*out_renderObject_ptr = new CXRenderObject(_rendObjects[0]);
		return true;
	}

	//else there are more than 1 rendering objects :D (at least 2)

	float minDist = _rendObjects[0].GetSurfDistance(fromPoint);
	int targetIndex = 0;

	//from the second (because we used the first one)
	for (size_t i = 1; i < _rendObjects.size(); i++)
	{
		float currentDist = _rendObjects[i].GetSurfDistance(fromPoint);

		//if current distance is smaller than the min distance, update :D
		if (minDist > currentDist)
		{
			minDist = currentDist;
			targetIndex = i;
		}
	}

	*out_distance = minDist;

	//change PTR!! NOT CONTENT
	*out_renderObject_ptr = new CXRenderObject(_rendObjects[targetIndex]);

	return true;
}

float CXRenderScene::GetClosestDistance(Vec3 fromPoint) const
{
	float outDist;
	CXRenderObject* renderObj_sharedPtr_USELESS = nullptr;
	TryGetClosestDistance(fromPoint, &outDist, &renderObj_sharedPtr_USELESS);

	return outDist;
}

//get's the list of the render objects but promise not to modify it :D
const std::vector<CXRenderObject>& CXRenderScene::GetRendObjects() const
{
	return _rendObjects;
}