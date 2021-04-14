#pragma once

struct CXMath
{
public:
	/// <summary>
	/// Linear interpolates between two values
	/// </summary>
	static float Lerp(float a, float b, float t);

	/// <summary>
	/// Linear interpolates between two values (precise)
	/// </summary>
	static float PrecLerp(float a, float b, float t);
	
	/// <summary>
	/// clamps the value between min and max
	/// </summary>
	static float Clamp(float value, float min, float max);

	/// <summary>
	/// clamps the value between 0 and 1
	/// </summary>
	static float Clamp01(float value);
};