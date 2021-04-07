#pragma once

#include "cece_vector3.h"
#include "cece_vector4.h"

namespace cece {
	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(int value);
		Matrix4(const Matrix4& otherMatrix4);
		Matrix4(float values[16]);

		inline const float& operator[](int index) const { return element[index]; }
		inline float& operator[](int index) { return element[index]; }

		Matrix4 operator*(const Matrix4& otherMatrix);
		Matrix4 operator*(const float scalar);
		Vector4 operator*(const Vector4& vector);

		Matrix4 operator-();

		void print() const;
		void printTransposed() const;
		float* c_arr() const;
		Matrix4 asTransposed();

	public:
		mutable float element[16];
		
	private:
		Matrix4 MultiplyMatrices(const Matrix4& left_mat, const Matrix4& right_mat);
		Matrix4 MultiplyWithScalar(const Matrix4& left_mat, const float scalar);
		Vector4 MultiplyWithVector(const Matrix4& mat, const Vector4& vec);
	};

	Matrix4 createIdentityMatrix();
	Matrix4 createEmptyMatrix();
	Matrix4 createTranslationMatrix(const Vector3& vector3);
	Matrix4 createTranslationMatrix(float delta_x, float delta_y, float delta_z);
	Matrix4 createScalingMatrix(float scale);
	Matrix4 createScalingMatrix(float scale_x, float scale_y, float scale_z);
	Matrix4 createXRotationMatrix(float angle);
	Matrix4 createYRotationMatrix(float angle);
	Matrix4 createZRotationMatrix(float angle);
}