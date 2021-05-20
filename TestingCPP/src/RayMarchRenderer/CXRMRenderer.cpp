#include "CXRMRenderer.h"

static const float DEFAULT_FAR_VIEW_DISTANCE = 100.0f;

CXRayMarchInfo CXRMRenderer::RayMarchFrom( const Vec3& rayOrigin, const Vec3& rayDirection ) const
{
	return m_RenderScene_ptr->RayMarchTo( rayOrigin, rayDirection, m_Camera );
}

CXRayMarchInfo CXRMRenderer::RayMarchFromCam( const Vec3& rayDirection ) const
{
	return RayMarchFrom( m_Camera.position, rayDirection );
}

//public

CXRMRenderer::CXRMRenderer( CXRenderScene*& renderScene_ptr, const CXCamera& camera ) :
	m_RenderScene_ptr( renderScene_ptr ), m_Camera( camera ) {}

CXRMRenderer::~CXRMRenderer()
{
	if ( m_RenderScene_ptr )
		delete m_RenderScene_ptr;
}

const CXRenderScene*& CXRMRenderer::GetRenderScene_Ptr()
{
	return m_RenderScene_ptr;
}

static std::mutex s_BitMapRenderMutex;

void CXRMRenderer::RenderPixel( CXBitMap* targetBitmap_Ptr, int x, int y ) const
{
	CXColor finalPixel = OnPixelLoop( x, y, targetBitmap_Ptr->GetWidth(), targetBitmap_Ptr->GetHeight() );

	std::lock_guard<std::mutex> setColorLock( s_BitMapRenderMutex );
	targetBitmap_Ptr->SetColor( finalPixel, x, y );
}

void CXRMRenderer::RenderBitmapBlock( CXBitMap* targetBitmap_Ptr, int startX, int startY,
	int blockWidth, int blockHeight ) const
{
	for ( int y = startY; y < startY + blockHeight; y++ )
		for ( int x = startX; x < startX + blockWidth; x++ )
			RenderPixel( targetBitmap_Ptr, x, y );
}

static const unsigned int MAX_THREAD_COUNT = std::thread::hardware_concurrency();

void CXRMRenderer::RenderToBitmap( CXBitMap& targetBitmap )
{
	int width = targetBitmap.GetWidth(),
		height = targetBitmap.GetHeight();

	size_t totalPixelCount = width * height;

	size_t pixPerRendBlock = totalPixelCount / MAX_THREAD_COUNT;

	size_t RenderBlockAvrgSide = static_cast<unsigned int>( sqrtf( static_cast<float>( pixPerRendBlock ) ) );

	size_t blockWidthCount = width / RenderBlockAvrgSide,
		blockHeightCount = height / RenderBlockAvrgSide;

	size_t lastRendBlockWidth = width - ( RenderBlockAvrgSide * blockWidthCount );
	size_t lastRendBlockHeight = height - ( RenderBlockAvrgSide * blockHeightCount );

	bool hasExtraWidth = lastRendBlockWidth > 0, hasExtraHeight = lastRendBlockHeight > 0;

	for ( size_t rBlockY = 0; rBlockY < blockHeightCount; rBlockY++ )
	{
		for ( size_t rBlockX = 0; rBlockX < blockWidthCount; rBlockX++ )
		{
			/*m_RenderFutures.push_back(
				std::async(std::launch::async, &CXRMRenderer::RenderBitmapBlock, this, &targetBitmap,
					rBlockX * RenderBlockAvrgSide, rBlockY * RenderBlockAvrgSide, RenderBlockAvrgSide, RenderBlockAvrgSide)
			);*/

			RenderBitmapBlock( &targetBitmap,
				rBlockX * RenderBlockAvrgSide, rBlockY * RenderBlockAvrgSide, RenderBlockAvrgSide, RenderBlockAvrgSide );
		}
	}

	//loop in the whole img (this as the UV of the camera)
	//for (int y = 0; y < height; y++)
	//{
	//	for (int x = 0; x < width; x++)
	//	{
	//		CXColor finalPixel = OnPixelLoop(x, y, width, height);

	//		targetBitmap.SetColor(finalPixel, x, y);

	//		/*m_RenderFutures.push_back(
	//			std::async(std::launch::async, &CXRMRenderer::RenderPixel, this, &targetBitmap, x, y)
	//		);*/
	//	}
	//}
}

CXColor CXRMRenderer::OnPixelLoop( const int& x, const int& y, const int& width, const int& height ) const
{
	float resDiv = CXMath::Max( static_cast<float>( width ), static_cast<float>( height ) );

	float uv_x = (float) x / resDiv,
		uv_y = (float) y / resDiv;

	float centerX = ( static_cast<float>( width ) / resDiv ) / 2.0f,
		centerY = ( static_cast<float>( height ) / resDiv ) / 2.0f;

	float camUV_x = uv_x - centerX, camUV_y = uv_y - centerY;

	Vec3 rayDirFromCam = m_Camera.GetRayDirection( camUV_x, camUV_y );

	//each pixel (which is UV :D)
	CXColor finalColor( 0, 0, 0 );

	CXRayMarchInfo rayMarchFromCamInfo = RayMarchFromCam( rayDirFromCam );


	if ( rayMarchFromCamInfo.isHit )
	{
		finalColor = GET_MATERIAL( rayMarchFromCamInfo )->
			OnPixel( x, y, width, height, m_RenderScene_ptr, rayMarchFromCamInfo, m_Camera );
	}
	else
	{
		//make not completely black
		static CXColor tempBackground = CXColor::FromGreyScale( 0.2f );

		finalColor = tempBackground;
	}

	return finalColor;
}

CXBitMap* CXRMRenderer::RenderToBitmap( int width, int height )
{
	CXBitMap* resultBitmap = new CXBitMap( width, height );

	RenderToBitmap( *resultBitmap );

	return resultBitmap;
}
