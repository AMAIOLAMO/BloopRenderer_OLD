#pragma once

#include <math.h>
#include <string>

struct Vec3
{
public:
	float x, y, z;

	enum class DV
	{
		zero, one,

		// ------- DIRECTION ------- //

		left, right,
		up, down,
		forward, backward
	};

	/// <summary>
	/// Creates an empty vector with default value of 0, 0, 0
	/// </summary>
	Vec3();

	Vec3(float _x, float _y, float _z);

	/// <summary>
	/// Copies the target vector (Deep copy)
	/// </summary>
	Vec3(const Vec3& other);

	explicit Vec3(const DV& defaultVal);

	/// <summary>
	/// Normalizes this vector for it's length to be 1
	/// </summary>
	void Normalize();

	/// <summary>
	/// Set's the length of this vector
	/// </summary>
	void SetLength(float length);

	/// <summary>
	/// Set's the vector
	/// </summary>
	void Set(float _x, float _y, float _z);

	/// <summary>
	/// Get's the dot product of the two vectors
	/// </summary>
	float Dot(const Vec3& other) const;

	/// <summary>
	/// Get's the cross product of the two vectors
	/// Cross get's the perpendicular of the vectors (the dot as the height)
	/// </summary>
	Vec3 Cross(const Vec3& other) const;

	/// <summary>
	/// Get's the length of the vector
	/// </summary>
	float GetLength() const;

	/// <summary>
	/// Get's the length of the vector but squared
	/// </summary>
	float GetLengthSqr() const;

	/// <summary>
	/// Get's the string representation of this vector
	/// </summary>
	std::string ToString() const;

#pragma region Operator overrides

	Vec3 operator+ (const Vec3& other) const;
	void operator+= (const Vec3& other);

	Vec3 operator- (const Vec3& other) const;
	void operator-= (const Vec3& other);

	Vec3 operator* (const Vec3& other) const;
	void operator*= (const Vec3& other);

	Vec3 operator/ (const Vec3& other) const;
	void operator/= (const Vec3& other);


	Vec3 operator* (float scale) const;
	void operator*= (float scale);

	Vec3 operator/ (float scale) const;
	void operator/= (float scale);

	bool operator==(const Vec3& other) const;

	Vec3 operator- () const;

#pragma endregion

#pragma region Static helpers

	/// <summary>
	/// Get's the dot product of the two vectors
	/// </summary>
	static float Dot(const Vec3& a, const Vec3& b);

	/// <summary>
	/// Get's the cross product of the two vectors
	/// Cross get's the perpendicular of the vectors (the dot as the height)
	/// </summary>
	static Vec3 Cross(const Vec3& a, const Vec3& b);

	/// <summary>
	/// Copies the new vector and set it to a specified length
	/// </summary>
	static Vec3 GetLenVect(const Vec3& a, float len);

	/// <summary>
	/// Copies the target vector and normalize the copied vector
	/// </summary>
	static Vec3 GetNormalized(const Vec3& a);

#pragma endregion

};