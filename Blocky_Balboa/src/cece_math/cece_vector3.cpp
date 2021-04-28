#include <cstdio>
#include <cstdlib>
//#include <utility>

#include "cece_vector3.h"

using namespace cece;

static float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;						  // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);            // what the fuck? 
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));  // 1st iteration
	y = y * (threehalfs - (x2 * y * y));  // 2nd iteration, this can be removed

	return y;
}

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(int value)
{
	x = float(value);
	y = float(value);
	z = float(value);
}

Vector3::Vector3(const Vector3& otherVector3)
{
	x = otherVector3.x;
	y = otherVector3.y;
	z = otherVector3.z;
}

Vector3::Vector3(float values[3])
{
	x = values[0];
	y = values[1];
	z = values[2];
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3 Vector3::operator-()
{
	return *this * -1.0f;
}

Vector3& Vector3::operator+=(const Vector3& otherVector3)
{
	*this = *this + otherVector3;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& otherVector3)
{
	*this = *this - otherVector3;
	return *this;
}

Vector3& Vector3::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector3& Vector3::operator/=(const float scalar)
{
	*this = *this / scalar;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& otherVector3) const
{
	return {
		this->x + otherVector3.x ,
		this->y + otherVector3.y ,
		this->z + otherVector3.z
	};
}

Vector3 Vector3::operator-(const Vector3& otherVector3) const
{
	return {
		this->x - otherVector3.x ,
		this->y - otherVector3.y ,
		this->z - otherVector3.z ,
	};
}

Vector3 cece::Vector3::operator*(const float scalar) const
{
	return {
		this->x * scalar,
		this->y * scalar,
		this->z * scalar,
	};
}

Vector3 Vector3::operator/(const float scalar) const
{
	return {
		this->x / scalar,
		this->y / scalar,
		this->z / scalar,
	};
}

void Vector3::Print() const
{
	printf("<%.4f %.4f %.4f>\n", x, y, z);
}

void Vector3::normalize()
{
	float inverse_sqrt = Q_rsqrt(x * x + y * y + z * z);
	*this *= inverse_sqrt;
}

float Vector3::length() const
{
	return sqrtf(lengthSquare());
}

float Vector3::lengthSquare() const
{
	return x * x + y * y + z * z;
}

float Vector3::DotMultiply(const Vector3& left_vector, const Vector3& right_vector) const
{
	return
		left_vector.x * right_vector.x +
		left_vector.y * right_vector.y +
		left_vector.z * right_vector.z;
}

Vector3 Vector3::CrossMultiply(const Vector3& otherVector3) const
{
	return {
		y * otherVector3.z - z * otherVector3.y,
		z * otherVector3.x - x * otherVector3.z,
		x * otherVector3.y - y * otherVector3.x,
	};
}

Vector3 cece::operator*(const float scalar, const Vector3& vector)
{
	return {
		vector.x * scalar,
		vector.y * scalar,
		vector.z * scalar,
	};
}

Vector3 cece::operator-(const Point& to, const Point& from)
{
	return Vector3(to.x - from.x, to.y - from.y, to.z - from.z);
}
