#include "CXVector.h"

Vec3::Vec3() :
	x(0), y(0), z(0) {}

Vec3::Vec3(float _x, float _y, float _z) :
	x(_x), y(_y), z(_z) {}

Vec3::Vec3(const Vec3& other) :
	x(other.x), y(other.y), z(other.z) {}

Vec3::Vec3(const DV& defaultVal)
{
	switch (defaultVal)
	{
	case DV::zero:     Set(0, 0, 0);
		break;
	case DV::one:      Set(1, 1, 1);
		break;
	case DV::left:     Set(-1, 0, 0);
		break;
	case DV::right:    Set(1, 0, 0);
		break;
	case DV::up:       Set(0, 1, 0);
		break;
	case DV::down:     Set(0, -1, 0);
		break;
	case DV::forward:  Set(0, 0, 1);
		break;
	case DV::backward: Set(0, 0, -1);
		break;
	default:
		throw std::exception("If you see this error, that means you may have used a DefaultValues\
			in a vector3 that doesn't even have cased");
	}
}

// ------------- VARIABLES ------------- //

void Vec3::SetLength(float length)
{
	//float scaleToNormalize = ;
	*this *= length / GetLength();
}

void Vec3::Normalize()
{
	SetLength(1.0f);
}

void Vec3::Set(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}

void Vec3::Map(float mapFunc(const float&))
{
	Set(mapFunc(x), mapFunc(y), mapFunc(z));
}

void Vec3::Map(float mapFunc(float))
{
	Set(mapFunc(x), mapFunc(y), mapFunc(z));
}

float Vec3::Dot(const Vec3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::Cross(const Vec3& other) const
{
	return Vec3(y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

float Vec3::GetLength() const
{
	return sqrtf(GetLengthSqr());
}

float Vec3::GetLengthSqr() const
{
	return x * x + y * y + z * z;
}

std::string Vec3::ToString() const
{
	return std::string("(") + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

// ------------- OPERATORS ------------- //

#pragma region Operator Overloads

Vec3 Vec3::operator+ (const Vec3& other) const
{
	return Vec3(x + other.x, y + other.y, z + other.z);
}

void Vec3::operator+=(const Vec3& other)
{
	*this = *this + other;
}


Vec3 Vec3::operator- (const Vec3& other) const
{
	return Vec3(x - other.x, y - other.y, z - other.z);
}

void Vec3::operator-=(const Vec3& other)
{
	*this = *this - other;
}


Vec3 Vec3::operator* (const Vec3& other) const
{
	return Vec3(x * other.x, y * other.y, z * other.z);
}

void Vec3::operator*=(const Vec3& other)
{
	*this = *this * other;
}


Vec3 Vec3::operator/ (const Vec3& other) const
{
	return Vec3(x / other.x, y / other.y, z / other.z);
}

void Vec3::operator/=(const Vec3& other)
{
	*this = *this / other;
}



Vec3 Vec3::operator* (float scale) const
{
	return Vec3(x * scale, y * scale, z * scale);
}

void Vec3::operator*=(float scale)
{
	*this = *this * scale;
}


Vec3 Vec3::operator/ (float scale) const
{
	return Vec3(x / scale, y / scale, z / scale);
}

void Vec3::operator/=(float scale)
{
	*this = *this / scale;
}


bool Vec3::operator==(const Vec3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}


Vec3 Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}

Vec3 Vec3::Min(const Vec3& a, const Vec3& b)
{
	return Vec3(CXMath::Min(a.x, b.x), CXMath::Min(a.y, b.y), CXMath::Min(a.z, b.z));
}

Vec3 Vec3::Max(const Vec3& a, const Vec3& b)
{
	return Vec3(CXMath::Max(a.x, b.x), CXMath::Max(a.y, b.y), CXMath::Max(a.z, b.z));
}

#pragma endregion

// ------------- HELPERS ------------- //

#pragma region Static helpers

float Vec3::Dot(const Vec3& a, const Vec3& b)
{
	return a.Dot(b);
}

Vec3 Vec3::Cross(const Vec3& a, const Vec3& b)
{
	return a.Cross(b);
}

Vec3 Vec3::GetLenVect(const Vec3& a, float len)
{
	float vecLen = a.GetLength();

	//if already same len then we don't calculate
	if (vecLen == len)
		return a;
	//else is different len

	return GetNormalized(a) * len;
}

Vec3 Vec3::GetNormalized(const Vec3& a)
{
	//we copy a vector
	Vec3 result(a);
	result.Normalize();
	return result;
}

#pragma endregion
