#include <cstdio>
#include <cstdlib>

#include "cece_vector4.h"

using namespace cece;

Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vector4::Vector4(int value)
{
	x = float(value);
	y = float(value);
	z = float(value);
	w = float(value);
}

Vector4::Vector4(const Vector4& otherVector4)
{
	x = otherVector4.x;
	y = otherVector4.y;
	z = otherVector4.z;
	w = otherVector4.w;
}

Vector4::Vector4(const Vector3& vector3, float _w)
{
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	w = _w;
}

Vector4::Vector4(float values[3], float _w)
{
	x = values[0];
	y = values[1];
	z = values[2];
	w = _w;
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Vector4 Vector4::operator-()
{
	return *this * -1.0f;
}

Vector4& Vector4::operator+=(const Vector4& otherVector4)
{
	*this = *this + otherVector4;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& otherVector4)
{
	*this = *this - otherVector4;
	return *this;
}

Vector4& Vector4::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector4& Vector4::operator/=(const float scalar)
{
	*this = *this / scalar;
	return *this;
}

Vector4 Vector4::operator+(const Vector4& otherVector4)
{
	return {
		this->x + otherVector4.x,
		this->y + otherVector4.y,
		this->z + otherVector4.z,
		this->w + otherVector4.w
	};
}

Vector4 Vector4::operator-(const Vector4& otherVector4)
{
	return {
		this->x - otherVector4.x,
		this->y - otherVector4.y,
		this->z - otherVector4.z,
		this->w - otherVector4.w
	};
}

Vector4 cece::Vector4::operator*(const float scalar)
{
	return {
		this->x * scalar,
		this->y * scalar,
		this->z * scalar,
		this->w * scalar
	};
}

Vector4 Vector4::operator/(const float scalar)
{
	return {
		this->x / scalar,
		this->y / scalar,
		this->z / scalar,
		this->w / scalar
	};
}

float Vector4::operator*(const Vector4& otherVector4)
{
	return DotMultiply(*this, otherVector4);
}

void Vector4::Print() const
{
	printf("<%.4f %.4f %.4f %.4f>", x, y, z, w);
}

Vector3 Vector4::asVector3() const
{
	return { x, y, z };
}

float Vector4::DotMultiply(const Vector4& left_vector, const Vector4& right_vector)
{
	return
		left_vector.x * right_vector.x +
		left_vector.y * right_vector.y +
		left_vector.z * right_vector.z +
		left_vector.w * right_vector.w;
}