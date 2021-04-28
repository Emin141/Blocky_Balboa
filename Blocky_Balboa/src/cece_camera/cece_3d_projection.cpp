#include <cstdlib>
#include <cstdio>

#include "cece_3d_projection.h"

using namespace cece;
static const float PI = 4.0f * atanf(1);

//static float Q_rsqrt(float number)
//{
//	long i;
//	float x2, y;
//	const float threehalfs = 1.5F;
//
//	x2 = number * 0.5F;
//	y = number;
//	i = *(long*)&y;						  // evil floating point bit level hacking
//	i = 0x5f3759df - (i >> 1);            // what the fuck? 
//	y = *(float*)&i;
//	y = y * (threehalfs - (x2 * y * y));  // 1st iteration
//	y = y * (threehalfs - (x2 * y * y));  // 2nd iteration, this can be removed
//
//	return y;
//}
//
//Vector3 cece::unit_distance(const Vector3& from, const Vector3& to)
//{
//	Vector3 distance;
//
//	distance[0] = to[0] - from[0];
//	distance[1] = to[1] - from[1];
//	distance[2] = to[2] - from[2];
//
//	float rsqrt = Q_rsqrt(
//		distance[0] * distance[0] +
//		distance[1] * distance[1] +
//		distance[2] * distance[2]
//	);
//
//	distance[0] *= rsqrt;
//	distance[1] *= rsqrt;
//	distance[2] *= rsqrt;
//
//	return distance;
//}

//Matrix4 cece::ViewMatrix(const Vector3& camera_position, const Vector3& target_position, Vector3& up_direction)
//{
//	Matrix4 translate_to_world_origin;
//	translate_to_world_origin.createTranslationMatrix(-camera_position[0], -camera_position[1], -camera_position[2]);
//
//	Vector3 forward_direction;
//	forward_direction = unit_distance(camera_position, target_position);
//
//	Vector3 right_direction = CrossMultiply(forward_direction, up_direction);
//
//	up_direction = CrossMultiply(right_direction, forward_direction);           //????????
//
//	Matrix4 rotate_to_negative_z;
//
//	rotate_to_negative_z[0] = right_direction[0];
//	rotate_to_negative_z[1] = up_direction[0];
//	rotate_to_negative_z[2] = -forward_direction[0];
//
//	rotate_to_negative_z[4] = right_direction[1];
//	rotate_to_negative_z[5] = up_direction[1];
//	rotate_to_negative_z[6] = -forward_direction[1];
//
//	rotate_to_negative_z[8] = right_direction[2];
//	rotate_to_negative_z[9] = up_direction[2];
//	rotate_to_negative_z[10] = -forward_direction[2];
//
//	return rotate_to_negative_z * translate_to_world_origin;
//}

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