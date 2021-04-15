#pragma once

struct CXMath
{
public:
	/// <summary>
	/// Linear interpolates between two values
	/// </summary>
	static float Lerp(const float& a, const float& b, const float& t);

	/// <summary>
	/// Linear interpolates between two values (precise)
	/// </summary>
	static float PrecLerp(const float& a, const float& b, const float& t);
	
	/// <summary>
	/// clamps the value between min and max
	/// </summary>
	static float Clamp(const float& value, const float& min, const float& max);

	/// <summary>
	/// clamps the value between 0 and 1
	/// </summary>
	static float Clamp01(const float& value);

	/// <summary>
	/// get's the minimum between two values
	/// </summary>
	static float Min(const float& a, const float& b);

	/// <summary>
	/// get's the maximum between two values
	/// </summary>
	static float Max(const float& a, const float& b);

	/// <summary>
	/// Limit the value under a certain threshold
	/// </summary>
	static float LimitMax(const float& value, const float& threshold);

	/// <summary>
	/// Limit the value above a certain threshold
	/// </summary>
	static float LimitMin(const float& value, const float& threshold);
};