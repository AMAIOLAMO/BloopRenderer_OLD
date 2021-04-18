#include "CXColor.h"

// -------------------------- CXCOLOR -------------------------- //

CXColor::CXColor() { SetColor(0, 0, 0); }

CXColor::CXColor(float _r, float _g, float _b) { SetColor(_r, _g, _b); }

CXColor::~CXColor() {}

void CXColor::SetColor(float _r, float _g, float _b)
{
	_r = CXMath::Clamp01(_r);
	_g = CXMath::Clamp01(_g);
	_b = CXMath::Clamp01(_b);

	r = _r; g = _g; b = _b;
}

void CXColor::SetColor(const CXColor& other)
{
	SetColor(other.r, other.g, other.b);
}

const float FLOATCOLOR_TO_UCHAR_SCALE = 255.0f;

unsigned char* CXColor::ToUnsignedCharBlock()
{
	unsigned char* result = new unsigned char[3]
	{
		static_cast<unsigned char>(r * FLOATCOLOR_TO_UCHAR_SCALE),
		static_cast<unsigned char>(g * FLOATCOLOR_TO_UCHAR_SCALE),
		static_cast<unsigned char>(b * FLOATCOLOR_TO_UCHAR_SCALE)
	};

	return result;
}

CXColor CXColor::FromGreyScale(float greyscale)
{
	return CXColor(greyscale, greyscale, greyscale);
}

CXColor CXColor::operator+(const CXColor& color) const
{
	return CXColor(r + color.r, g + color.g, b + color.b);
}

void CXColor::operator+=(const CXColor& color)
{
	*this = *this + color;
}

CXColor CXColor::operator*(const float& intensity) const
{
	CXColor result(*this);
	result *= intensity;
	return result;
}

void CXColor::operator*=(const float& grayScale)
{
	SetColor(r * grayScale, g * grayScale, b * grayScale);
}

// -------------------------- UCXCOLOR -------------------------- //

//UCXColor::UCXColor()
//{
//	SetColor(0, 0, 0);
//}
//
//UCXColor::UCXColor(unsigned char _r, unsigned char _g, unsigned char _b)
//{
//	SetColor(_r, _g, _b);
//}
//
//UCXColor::~UCXColor() {}
//
//void UCXColor::SetColor(unsigned char _r, unsigned char _g, unsigned char _b)
//{
//	r = _r; g = _g; b = _b;
//}
//
//void UCXColor::SetColor(const UCXColor& other)
//{
//	SetColor(other.r, other.g, other.b);
//}
