#include <cstdlib>
#include <cstdio>

#include "cece_camera.h"

using namespace cece;
static const float PI = 4.0f * atanf(1);
extern float g_delta_time;
float speed = 20.0f;
float rot_speed = 115.0f;

Camera::Camera()
{
	position = Vector3(0.0f, 0.0f, 4.0f);
	yaw = 0.0f;
	pitch = 0.0f;

	proj = ProjectionMatrix();
}

Matrix4 Camera::getMVP()
{
	return proj * ViewMatrix();
}

Matrix4 Camera::ViewMatrix()
{
	Matrix4 translate = createTranslationMatrix(-1.0f * position);

	Matrix4 undo_yaw = createYRotationMatrix(yaw);
	Matrix4 undo_pitch = createXRotationMatrix(pitch);

	return undo_pitch * undo_yaw * translate;
}

Matrix4 Camera::ProjectionMatrix()
{
	Matrix4 perspective_transform(0);

	constexpr float FOV = 45.f;
	constexpr float aspect_ratio = 16.0f / 9.0f;
	constexpr float far = 500.0f;
	constexpr float near = 0.1f;

	float cot = 1.0f / tanf(PI / 180.0f * FOV / 2.0f);

	perspective_transform[0] = cot / aspect_ratio;
	perspective_transform[5] = cot;
	perspective_transform[10] = -(far + near) / (far - near);
	perspective_transform[11] = -1;
	perspective_transform[14] = -(2 * far * near) / (far - near);

	return perspective_transform;
}