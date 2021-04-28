#pragma once
#include <cstdlib>
#include "../cece_math/cece_vector3.h"
#include "../cece_math/cece_matrix4.h"

namespace cece {
	//Vector3 unit_distance(const Vector3& from, const Vector3& to);
	Matrix4 ViewMatrix(const Vector3& camera_position, const Vector3& forward_direction, Vector3& up_direction);
	Matrix4 ProjectionMatrix(const float FOV, const float aspect_ratio, const float near, const float far);
}