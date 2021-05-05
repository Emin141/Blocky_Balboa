#include <cstdlib>
#include <cstdio>

#include "cece_3d_projection.h"

using namespace cece;
static const float PI = 4.0f * atanf(1);

Matrix4 cece::ViewMatrix(const Vector3& camera_position, const Vector3& forward_direction, Vector3& up_direction)
{
	Vector3 right_direction = forward_direction.CrossMultiply(up_direction);
	float elements[] = {
		right_direction.x, up_direction.x, -1 * forward_direction.x, 0,
		right_direction.y, up_direction.y, -1 * forward_direction.y, 0,
		right_direction.z, up_direction.z, -1 * forward_direction.z, 0,
		-1 * camera_position.x, -1 * camera_position.y, -1 * camera_position.z, 1
	};
	return elements;
}

Matrix4 cece::ProjectionMatrix(const float FOV, const float aspect_ratio, const float near, const float far)
{
	Matrix4 perspective_transform(0);

	float cot = 1.0f / tanf(PI / 180.0f * FOV / 2.0f);

	perspective_transform[0] = cot / aspect_ratio;
	perspective_transform[5] = cot;
	perspective_transform[10] = -(far + near) / (far - near);
	perspective_transform[11] = -1;
	perspective_transform[14] = -(2 * far * near) / (far - near);

	return perspective_transform;
}