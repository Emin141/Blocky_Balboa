#include <cstdlib>
#include <cstdio>
#include <utility>

#include "cece_matrix4.h"

using namespace cece;

Matrix4::Matrix4()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			element[4 * i + j] = i == j ? 1.0f : 0.0f;
		}
}

Matrix4::Matrix4(int value)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			element[4 * i + j] = float(value);
		}
}

Matrix4::Matrix4(const Matrix4& otherMatrix4)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			element[4 * i + j] = otherMatrix4[4 * i + j];
		}
}

Matrix4::Matrix4(float values[16])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			element[4 * i + j] = values[4 * i + j];
		}
}

Matrix4 Matrix4::operator*(const Matrix4& otherMatrix)
{
	return MultiplyMatrices(*this, otherMatrix);
}

Matrix4 Matrix4::operator*(const float scalar)
{
	return MultiplyWithScalar(*this, scalar);
}

Vector4 Matrix4::operator*(const Vector4& vector)
{
	return MultiplyWithVector(*this, vector);
}

Matrix4 Matrix4::operator-()
{
	return *this * -1.0f;
}

void Matrix4::print() const
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%.4f ", element[4 * i + j]);
		}
		printf("\n");
	}	printf("\n");
}

void Matrix4::printTransposed() const
{
	printf("%.4f %.4f %4f %4f\n",
		element[0], element[4], element[8], element[12]);
	printf("%.4f %.4f %4f %4f\n",
		element[1], element[5], element[9], element[13]);
	printf("%.4f %.4f %4f %4f\n",
		element[2], element[6], element[10], element[14]);
	printf("%.4f %.4f %4f %4f\n\n",
		element[3], element[7], element[11], element[15]);
}

Matrix4 cece::createIdentityMatrix()
{
	return Matrix4();
}

Matrix4 cece::createEmptyMatrix()
{
	return Matrix4(0);
}

Matrix4 cece::createTranslationMatrix(const Vector3& vector3)
{
	Matrix4 result;
	result.element[12] = vector3.x;
	result.element[13] = vector3.y;
	result.element[14] = vector3.z;
	return result;
}

Matrix4 cece::createTranslationMatrix(float delta_x, float delta_y, float delta_z)
{
	Matrix4 result;
	result.element[12] = delta_x;
	result.element[13] = delta_y;
	result.element[14] = delta_z;
	return result;
}

Matrix4 cece::createScalingMatrix(float scale)
{
	Matrix4 result;
	result.element[0] = scale;
	result.element[5] = scale;
	result.element[10] = scale;
	return result;
}

Matrix4 cece::createScalingMatrix(float scale_x, float scale_y, float scale_z)
{
	Matrix4 result;
	result.element[0] = scale_x;
	result.element[5] = scale_y;
	result.element[10] = scale_z;
	return result;
}

Matrix4 cece::createXRotationMatrix(float angle)
{
	Matrix4 result;
	result.element[5] = cosf(angle);
	result.element[6] = sinf(angle);
	result.element[9] = -sinf(angle);
	result.element[10] = cosf(angle);
	return result;
}

Matrix4 cece::createYRotationMatrix(float angle)
{
	Matrix4 result;
	result.element[0] = cosf(angle);
	result.element[2] = -sinf(angle);
	result.element[8] = sinf(angle);
	result.element[10] = cosf(angle);
	return result;
}

Matrix4 cece::createZRotationMatrix(float angle)
{
	Matrix4 result;
	result.element[0] = cosf(angle);
	result.element[1] = sinf(angle);
	result.element[4] = -sinf(angle);
	result.element[5] = cosf(angle);
	return result;
}

float* Matrix4::c_arr() const
{
	return (float*)element;
}

Matrix4 Matrix4::asTransposed()
{
	float transposed[] = {
		element[0], element[4], element[8], element[12],
		element[1], element[5], element[9], element[13],
		element[2], element[6], element[10], element[14],
		element[3], element[7], element[11], element[15]
	};
	return transposed;
}

Matrix4 Matrix4::MultiplyMatrices(const Matrix4& left_mat, const Matrix4& right_mat)
{
	float result[16];
	for (int i = 0; i < 16; i++)
		result[i] = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result[i + j * 4] += left_mat[i + k * 4] * right_mat[k + j * 4];
			}
		}
	}

	return result;
}

Matrix4 Matrix4::MultiplyWithScalar(const Matrix4& left_mat, const float scalar)
{
	Matrix4 result(0);
	for (int i = 0; i < 16; i++)
		result[0] = left_mat[0] * scalar;
	return result;
}

Vector4 Matrix4::MultiplyWithVector(const Matrix4& mat, const Vector4& vec)
{
	float result[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	result[0] = mat[0] * vec.x + mat[4] * vec.y + mat[8] * vec.z + mat[12] * vec.w;
	result[1] = mat[1] * vec.x + mat[5] * vec.y + mat[9] * vec.z + mat[13] * vec.w;
	result[2] = mat[2] * vec.x + mat[6] * vec.y + mat[10] * vec.z + mat[14] * vec.w;
	result[3] = mat[3] * vec.x + mat[7] * vec.y + mat[11] * vec.z + mat[15] * vec.w;

	return result;
}