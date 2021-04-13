#include "CXMath.h"

float CXMath::Lerp(float a, float b, float t)
{
	return a + t * (a - b);
}

float CXMath::PrecLerp(float a, float b, float t)
{
	return (1.0f - t) * a + t * b;
}

float CXMath::Clamp(float value, float min, float max)
{
	return value < min ? min : (value > max ? max : value);
}

float CXMath::Clamp01(float value)
{
	return Clamp(value, 0.0f, 1.0f);
}
