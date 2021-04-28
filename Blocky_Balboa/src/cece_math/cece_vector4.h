#pragma once
#include "cece_vector3.h"

namespace cece {
	class Vector4
	{
	public:
		Vector4();
		Vector4(int value);
		Vector4(const Vector4& otherVector4);
		Vector4(const Vector3& vector3, float w = 1.0f);
		Vector4(float values[3], float w = 1.0f);
		Vector4(float x, float y, float z, float w = 1.0f);

		/*inline const float& operator[](int index) const { return element[index]; }
		inline float& operator[](int index) { return element[index]; }*/

		Vector4 operator+(const Vector4& otherVector4);
		Vector4 operator-(const Vector4& otherVector4);
		Vector4 operator*(const float scalar);
		Vector4 operator/(const float scalar);
		float operator*(const Vector4& otherVector4);

		Vector4 operator-();
		Vector4& operator+=(const Vector4& otherVector4);
		Vector4& operator-=(const Vector4& otherVector4);
		Vector4& operator*=(const float scalar);
		Vector4& operator/=(const float scalar);

		void Print() const;
		Vector3 asVector3() const;
		float DotMultiply(const Vector4& left_vector, const Vector4& right_vector);

	public:
		float x, y, z, w;

	};
}