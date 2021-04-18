#pragma once

#include "../Math/CXMath.h"

/// <summary>
/// float color by CXRedix
/// </summary>
struct CXColor
{
public:
	float r, g, b;

	CXColor();
	CXColor(float _r, float _g, float _b);

	~CXColor();

	/// <summary>
	/// Set's the current color to a new color
	/// </summary>
	void SetColor(float _r, float _g, float _b);

	/// <summary>
	/// Set's the current color as a new color (doesn't just apply, but copy :D)
	/// </summary>
	void SetColor(const CXColor& other);

	/// <summary>
	/// Convert's the color into a 1 byte unsigned char value 0 -> r, 1 -> g, 2 -> b; NOTE: MUST DELETE AFTER USING!!!
	/// </summary>
	unsigned char* ToUnsignedCharBlock();

	static CXColor FromGreyScale(float greyscale);

#pragma region operators

	CXColor operator+(const CXColor& color) const;
	void operator+=(const CXColor& color);

	CXColor operator*(const float& intensity) const;
	void operator*=(const float& intensity);

#pragma endregion
};
