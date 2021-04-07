#include <cstdlib>
#include <cstdio>

#include "cece_camera.h"

using namespace cece;
static const float PI = 4.0f * atanf(1);
extern float g_deltaTime;
float speed = 20.0f;
float rot_speed = 120.f;

Camera::Camera()
{
	position = Vector3(0.0f, 0.0f, 4.0f);
	yaw = 0.0f;
	pitch = 0.0f;

	forward = Vector3(0.0f, 0.0f, -1.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);
	right = Vector3(1.0f, 0.0f, 0.0f);

	proj = ProjectionMatrix();
}

void Camera::moveForward()
{
	position += forward * g_deltaTime * speed;
}

void Camera::moveBackward()
{
	position -= forward * g_deltaTime * speed;
}

void Camera::moveRight()
{
	position += right * g_deltaTime * speed;
}

void Camera::moveLeft()
{
	position -= right * g_deltaTime * speed;
}

void Camera::moveUp()
{
	position += up * g_deltaTime * speed;
}

void Camera::moveDown()
{
	position -= up * g_deltaTime * speed;
}

void Camera::yawRight()
{
	yaw += g_deltaTime * rot_speed;
	yaw = fmodf(yaw, 360.0f);
	forward = {
		cosf(PI / 180 * yaw - PI / 2),
		0.0f,
		sinf(PI / 180 * yaw - PI / 2)
	};
	right = forward.CrossMultiply(up);
}

void Camera::yawLeft()
{
	yaw -= g_deltaTime * rot_speed;
	yaw = fmodf(yaw, 360.0f);
	forward = {
		cosf(PI / 180 * yaw - PI / 2),
		0.0f,
		sinf(PI / 180 * yaw - PI / 2)
	};
	right = forward.CrossMultiply(up);
}

void Camera::pitchUp()
{
	pitch += g_deltaTime * rot_speed;
}

void Camera::pitchDown()
{
	pitch -= g_deltaTime * rot_speed;
}

Matrix4 Camera::getMVP()
{
	return proj * ViewMatrix();
}

Matrix4 Camera::ViewMatrix()
{
	Matrix4 translate = createTranslationMatrix(-1.0f * position);

	Matrix4 undo_yaw = createYRotationMatrix(PI / 180 * yaw);
	Matrix4 undo_pitch = createXRotationMatrix(PI / 180 * pitch);

	return undo_pitch * undo_yaw * translate;
}

Matrix4 Camera::ProjectionMatrix()
{
	Matrix4 perspective_transform(0);

	float FOV = 45.f;
	float aspect_ratio = 4.0f / 3.0f;
	float far = 100.0f;
	float near = 0.1f;

	float cot = 1.0f / tanf(PI / 180.0f * FOV / 2.0f);

	perspective_transform[0] = cot / aspect_ratio;
	perspective_transform[5] = cot;
	perspective_transform[10] = -(far + near) / (far - near);
	perspective_transform[11] = -1;
	perspective_transform[14] = -(2 * far * near) / (far - near);

	return perspective_transform;
}