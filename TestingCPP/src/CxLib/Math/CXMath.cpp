#include "CXMath.h"

float CXMath::Lerp(const float& a, const float& b, const float& t)
{
	return a + t * (a - b);
}

float CXMath::PrecLerp(const float& a, const float& b, const float& t)
{
	return (1.0f - t) * a + t * b;
}

float CXMath::Clamp(const float& value, const float& min, const float& max)
{
	return value < min ? min : (value > max ? max : value);
}

float CXMath::Clamp01(const float& value)
{
	return Clamp(value, 0.0f, 1.0f);
}

float CXMath::Min(const float& a, const float& b)
{
	return b < a ? b : a;
}

float CXMath::Max(const float& a, const float& b)
{
	return b > a ? b : a;
}
