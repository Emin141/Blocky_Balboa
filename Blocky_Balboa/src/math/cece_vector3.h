#pragma once

#include "cece_point.h"

namespace cece {
	class Vector3
	{
	public:
		Vector3();
		Vector3(int value);
		Vector3(const Vector3& otherVector3);
		Vector3(float values[3]);
		Vector3(float x, float y, float z);

		inline const float& operator[](int index) const
		{
			switch (index)
			{
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			case 2:
				return z;
				break;
			default:
				break;
			}
		}
		inline float& operator[](int index) {
			switch (index)
			{
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			case 2:
				return z;
				break;
			default:
				break;
			}
		}

		Vector3 operator+(const Vector3& otherVector3) const;
		Vector3 operator-(const Vector3& otherVector3) const;
		Vector3 operator*(const float scalar) const;
		Vector3 operator/(const float scalar) const;

		Vector3 operator-();
		Vector3& operator+=(const Vector3& otherVector3);
		Vector3& operator-=(const Vector3& otherVector3);
		Vector3& operator*=(const float scalar);
		Vector3& operator/=(const float scalar);

		void Print() const;
		void normalize();
		float length() const;
		float lengthSquare() const;

		float DotMultiply(const Vector3& left_vector, const Vector3& right_vector) const;
		Vector3 CrossMultiply(const Vector3& otherVector3) const;

	public:
		float x, y, z;
	};

	Vector3 operator*(const float scalar, const Vector3& vector);
	Vector3 operator-(const Point& from, const Point& to);
}
