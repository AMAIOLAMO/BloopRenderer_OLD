#include "CXRenderScene.h"

//instantiates the render scene with render objects
CXRenderScene::CXRenderScene() :
	m_RendObject_sharePtrs() {}

//simply just real copies the render object
CXRenderScene::CXRenderScene(const std::vector<std::shared_ptr<CXRenderObject>>& rendObject_sharePtrs) :
	m_RendObject_sharePtrs(rendObject_sharePtrs) {}

CXRenderScene::CXRenderScene(const CXRenderScene& other) :
	m_RendObject_sharePtrs(other.GetRendObject_sharePtrs()) {}

CXRenderScene& CXRenderScene::Add(const std::shared_ptr<CXRenderObject>& rendObject_sharePtr)
{
	m_RendObject_sharePtrs.push_back(rendObject_sharePtr);
	return *this; //for chaining methods together
}

CXRayMarchInfo CXRenderScene::RayMarchTo(const Vec3& rayOrigin, const Vec3& rayDirection,
	unsigned int maxMarchIteration, float minSurfaceDistance, float farViewDistance) const
{
	float distanceFromOriginMarched = .0f;

	bool isHit = false;

	Vec3 targetHitPoint(0, 0, 0);

	std::shared_ptr<CXRenderObject> targetRendObj_sharePtr = nullptr;

	//the iteration passed
	unsigned int marchIterationPassed;

	for (marchIterationPassed = 0; marchIterationPassed < maxMarchIteration; marchIterationPassed++)
	{
		targetHitPoint = rayOrigin + rayDirection * distanceFromOriginMarched;

		float closestSurfDistInSceneFromMarchedPoint;

		//imagine we draw a circle to the closest distance if didn't get any closest distance.... then no object :D
		if (!TryGetClosestDistance(targetHitPoint, &closestSurfDistInSceneFromMarchedPoint, &targetRendObj_sharePtr))
			continue;
		//else we got a distance with a marched point and the target render object

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

	return CXRayMarchInfo(targetHitPoint, marchIterationPassed, isHit, distanceFromOriginMarched, targetRendObj_sharePtr);
}

CXRayMarchInfo CXRenderScene::RayMarchTo(const Vec3& rayOrigin, const Vec3& rayDirection, const CXCamera& cam) const
{
	return RayMarchTo(rayOrigin, rayDirection, cam.maxMarchingIteration, cam.minSurfDistance, cam.farViewDistance);
}

CXRayMarchInfo CXRenderScene::RayMarchFromHitPoint(const Vec3& hitPoint, const Vec3& rayDir_Normalized, const CXCamera& cam) const
{
	return RayMarchTo(hitPoint + rayDir_Normalized, rayDir_Normalized, cam);
}

bool CXRenderScene::TryGetClosestDistance(const Vec3& fromPoint,
	float* const out_distance, std::shared_ptr<CXRenderObject>* const out_renderObject_ptr) const
{
	if (m_RendObject_sharePtrs.size() == 0)
	{
		*out_distance = NAN;
		return false;
	}
	//else

	if (m_RendObject_sharePtrs.size() == 1)
	{
		*out_distance = m_RendObject_sharePtrs[0]->renderBody_sharePtr->GetSignedDistance(fromPoint);

		//change content, BUT NOT POINTER
		*out_renderObject_ptr = m_RendObject_sharePtrs[0];
		return true;
	}

	//else there are more than 1 rendering objects :D (at least 2)

	float minDist = m_RendObject_sharePtrs[0]->renderBody_sharePtr->GetSignedDistance(fromPoint);
	int targetIndex = 0;

	//from the second (because we used the first one)
	for (size_t i = 1; i < m_RendObject_sharePtrs.size(); i++)
	{
		float currentDist = m_RendObject_sharePtrs[i]->renderBody_sharePtr->GetSignedDistance(fromPoint);

		//if current distance is smaller than the min distance, update :D
		if (minDist > currentDist)
		{
			minDist = currentDist;
			targetIndex = i;
		}
	}

	*out_distance = minDist;

	//change content, BUT NOT POINTER
	*out_renderObject_ptr = m_RendObject_sharePtrs[targetIndex];

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
	return m_RendObject_sharePtrs;
}

const std::vector<std::shared_ptr<CXRenderObject>>& CXRenderScene::GetRendObject_sharePtrs() const
{
	return m_RendObject_sharePtrs;
}
