#include "CXVector.h"

Vec3::Vec3(float _x, float _y, float _z)
{
	Set(_x, _y, _z);
}

Vec3::Vec3(const Vec3& other)
{
	Set(other.x, other.y, other.z);
}

Vec3::Vec3(const DV& defaultVal)
{
	switch (defaultVal)
	{
	case DV::zero:
		Set(0, 0, 0);
		break;
	case DV::one:
		Set(1, 1, 1);
		break;
	case DV::left:
		Set(-1, 0, 0);
		break;
	case DV::right:
		Set(1, 0, 0);
		break;
	case DV::up:
		Set(0, 1, 0);
		break;
	case DV::down:
		Set(0, -1, 0);
		break;
	case DV::forward:
		Set(0, 0, 1);
		break;
	case DV::backward:
		Set(0, 0, -1);
		break;
	default:
		throw std::exception("If you see this error, that means you may have used a DefaultValues in a vector3 that doesn't even have cased");
	}
}

void Vec3::SetLength(float length)
{
	float scaleToNormalize = length / GetLength();

	*this *= scaleToNormalize;
}

void Vec3::Normalize()
{
	SetLength(1.0f);
}

void Vec3::Set(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
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

#pragma region Operator Overloads

Vec3 Vec3::operator+ (const Vec3& other)
{
	return Vec3(x + other.x, y + other.y, z + other.z);
}

void Vec3::operator+=(const Vec3& other)
{
	*this = *this + other;
}


Vec3 Vec3::operator- (const Vec3& other)
{
	return Vec3(x - other.x, y - other.y, z - other.z);
}

void Vec3::operator-=(const Vec3& other)
{
	*this = *this - other;
}


Vec3 Vec3::operator* (const Vec3& other)
{
	return Vec3(x * other.x, y * other.y, z * other.z);
}

void Vec3::operator*=(const Vec3& other)
{
	*this = *this * other;
}


Vec3 Vec3::operator/ (const Vec3& other)
{
	return Vec3(x / other.x, y / other.y, z / other.z);
}

void Vec3::operator/=(const Vec3& other)
{
	*this = *this / other;
}



Vec3 Vec3::operator* (float scale)
{
	return Vec3(x * scale, y * scale, z * scale);
}

void Vec3::operator*=(float scale)
{
	*this = *this * scale;
}


Vec3 Vec3::operator/ (float scale)
{
	return Vec3(x / scale, y / scale, z / scale);
}

void Vec3::operator/=(float scale)
{
	*this = *this / scale;
}


bool Vec3::operator==(const Vec3& other)
{
	return x == other.x && y == other.y && z == other.z;
}


Vec3 Vec3::operator-()
{
	return Vec3(-x, -y, -z);
}

#pragma endregion

#pragma region Static helpers

float Vec3::Dot(const Vec3& a, const Vec3& b)
{
	return a.Dot(b);
}

Vec3 Vec3::Cross(const Vec3& a, const Vec3& b)
{
	return a.Cross(b);
}

float Vec3::GetLength(const Vec3& a)
{
	return a.GetLength();
}

float Vec3::GetLengthSqr(const Vec3& a)
{
	return a.GetLengthSqr();
}

Vec3 Vec3::GetNormalized(const Vec3& a)
{
	//we copy a vector
	Vec3 result(a);
	result.Normalize();
	return result;
}

#pragma endregion
