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
	template <typename T>
	static float Min(const T& a, const T& b)
	{
		return b < a ? b : a;
	}

	/// <summary>
	/// get's the maximum between two values
	/// </summary>
	template <typename T>
	static float Max(const T& a, const T& b)
	{
		return b > a ? b : a;
	}

	/// <summary>
	/// Limit the value under a certain threshold
	/// </summary>
	template <typename T>
	static float LimitMax(const T& value, const T& threshold)
	{
		return Min(value, threshold);
	}

	/// <summary>
	/// Limit the value above a certain threshold
	/// </summary>
	template <typename T>
	static float LimitMin(const T& value, const T& threshold)
	{
		return Max(value, threshold);
	}
};