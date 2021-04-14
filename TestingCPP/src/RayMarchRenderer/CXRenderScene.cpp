#include "CXRenderScene.h"

//instantiates the render scene with render objects
CXRenderScene::CXRenderScene() :
	_rendObject_sharePtrs() {}

//simply just real copies the render object
CXRenderScene::CXRenderScene(const std::vector<std::shared_ptr<CXRenderObject>>& rendObject_sharePtrs) :
	_rendObject_sharePtrs(rendObject_sharePtrs) {}

CXRenderScene::CXRenderScene(const CXRenderScene& other) :
	_rendObject_sharePtrs(other.GetRendObject_sharePtrs()) {}

CXRenderScene& CXRenderScene::Add(const std::shared_ptr<CXRenderObject>& rendObject_sharePtr)
{
	_rendObject_sharePtrs.push_back(rendObject_sharePtr);
	return *this; //for chaining methods together
}

CXRayMarchInfo CXRenderScene::RayMarch(const Vec3& rayOrigin, const Vec3& rayDirection,
	size_t maxMarchIteration, float minSurfaceDistance, float farViewDistance) const
{
	float distanceFromOriginMarched = .0f;

	bool isHit = false;

	Vec3 targetHitPoint(0, 0, 0);

	std::shared_ptr<CXRenderObject> targetRendObj_sharePtr = nullptr;

	for (std::size_t i = 0; i < maxMarchIteration; i++)
	{
		targetHitPoint = rayOrigin + rayDirection * distanceFromOriginMarched;

		float closestSurfDistInSceneFromMarchedPoint;

		//imagine we draw a circle to the closest distance if didn't get any closest distance.... then no object :D
		if (!TryGetClosestDistance(targetHitPoint, &closestSurfDistInSceneFromMarchedPoint, &targetRendObj_sharePtr))
			continue;

		//else we got a distance with a marched point and the target render object

		//float closestSurfDistInSceneFromMarchedPoint = GetClosestDistance(pointMarchedTo);

		distanceFromOriginMarched += closestSurfDistInSceneFromMarchedPoint;

		if (closestSurfDistInSceneFromMarchedPoint < minSurfaceDistance) //is hit :D (raymarch circle so small)
		{
			isHit = true;
			break;
		}
		//else
		if (distanceFromOriginMarched > farViewDistance) //bruh not hit??? :< shoot too far
			break;
	}

	return CXRayMarchInfo(targetHitPoint, isHit, distanceFromOriginMarched, targetRendObj_sharePtr);
}

bool CXRenderScene::TryGetClosestDistance(Vec3 fromPoint,
	float* const out_distance, std::shared_ptr<CXRenderObject>* const out_renderObject_ptr) const
{
	if (_rendObject_sharePtrs.size() == 0)
	{
		*out_distance = NAN;
		return false;
	}
	//else

	if (_rendObject_sharePtrs.size() == 1)
	{
		*out_distance = _rendObject_sharePtrs[0]->GetSurfDistance(fromPoint);

		//change content, BUT NOT POINTER
		*out_renderObject_ptr = _rendObject_sharePtrs[0];
		return true;
	}

	//else there are more than 1 rendering objects :D (at least 2)

	float minDist = _rendObject_sharePtrs[0]->GetSurfDistance(fromPoint);
	int targetIndex = 0;

	//from the second (because we used the first one)
	for (size_t i = 1; i < _rendObject_sharePtrs.size(); i++)
	{
		float currentDist = _rendObject_sharePtrs[i]->GetSurfDistance(fromPoint);

		//if current distance is smaller than the min distance, update :D
		if (minDist > currentDist)
		{
			minDist = currentDist;
			targetIndex = i;
		}
	}

	*out_distance = minDist;

	//change content, BUT NOT POINTER
	*out_renderObject_ptr = _rendObject_sharePtrs[targetIndex];

	return true;
}

float CXRenderScene::GetClosestDistance(const Vec3& fromPoint) const
{
	float outDist;
	std::shared_ptr<CXRenderObject>* renderObj_sharedPtr_USELESS = nullptr;
	TryGetClosestDistance(fromPoint, &outDist, renderObj_sharedPtr_USELESS);

	return outDist;
}

std::vector<std::shared_ptr<CXRenderObject>>& CXRenderScene::GetRendObject_sharePtrs()
{
	return _rendObject_sharePtrs;
}

const std::vector<std::shared_ptr<CXRenderObject>>& CXRenderScene::GetRendObject_sharePtrs() const
{
	return _rendObject_sharePtrs;
}