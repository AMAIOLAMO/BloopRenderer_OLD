#pragma once

#include <memory>

//#include "CXMaterial.h"
#include "CXRenderBody.h"

/// <summary>
/// A renderable object to pass into the CXScene
/// </summary>
class CXRenderObject
{
public:
	/*CXMaterial material;*/
	//a shared ptr that points to a render body
	std::shared_ptr<CXRenderBody> renderBody_sharePtr;

public:
	/*CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr, const CXMaterial& _material);*/

	CXRenderObject(const std::shared_ptr<CXRenderBody>& _renderBody_sharePtr);

	CXRenderObject(const CXRenderObject& other);

	~CXRenderObject();
};

//#include <math.h>
//#include <memory>
//
//class CXMaterial;
//
//#include "../../CxLib/Math/CXVector.h"
//#include "../../CxLib/BitMap/CXColor.h"
//
///// <summary>
///// A renderable object to pass into the CXScene
///// </summary>
//class CXRenderObject
//{
//public:
//	Vec3 position;
//	CXColor baseColor;
//	CXMaterial* material_ptr;
//
//public:
//	CXRenderObject(const Vec3& _position, const CXColor& _baseColor);
//
//	CXRenderObject(const Vec3& _position, const CXColor& _baseColor, CXMaterial*& _material_Ptr);
//
//	/// <summary>
//	/// Deep copies from another renderer object
//	/// </summary>
//	CXRenderObject(const CXRenderObject& other);
//
//	~CXRenderObject();
//
//	/// <summary>
//	/// Get's the distance between the target position to the specified from Position
//	/// </summary>
//	virtual float GetSurfDistance(const Vec3& fromPos) const abstract = 0;
//
//	/// <summary>
//	/// Get's the material color of this point on surface
//	/// </summary>
//	virtual CXColor GetMaterialColor(const Vec3& pointOnSurface) const;
//
//	/// <summary>
//	/// Get's the normal from the target point with the target precision (default as .01f)
//	/// </summary>
//	virtual Vec3 GetNormal(const Vec3& pointOnSurface) const;
//};