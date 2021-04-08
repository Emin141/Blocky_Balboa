#include "blocky_balboa.h"

static const float PI = 4.0f * atanf(1);

static float toRadians(float degrees_angle)
{
	return PI / 180.0f * degrees_angle;
}

BlockyBalboa::BlockyBalboa()
{
	m_position = { 0.0f, 0.0f, 0.0f };

	m_camera = new cece::Camera;

	m_euler_angle = { toRadians(-15.0f), toRadians(-90.0f), 0.0f };
	printf("Initial yaw: %f\n", m_euler_angle.y);

	m_camera_offeset = 15.0f * m_euler_angle.ToVector();
	m_camera->position = m_position - m_camera_offeset;
	m_camera->pitch = 15.0f;

	m_forward = { 0.0f, 0.0f, -1.0f };
	m_up = { 0.0f, 1.0f, 0.0f };
	m_right = { 1.0f, 0.0f, 0.0f };

	model_matrix = cece::createTranslationMatrix(-1.0f * m_position);

	m_Program->setUniform("mvp", m_camera->getMVP().c_arr());
	m_Program->setUniform("model_matrix", model_matrix.c_arr());

	lin_speed = 20.0f;
	rot_speed = 2.0f;
}

BlockyBalboa::~BlockyBalboa()
{
	delete m_camera;
}

void BlockyBalboa::updateCameraPosition()
{
	m_camera_offeset = 15.0f * m_euler_angle.ToVector();
	m_camera->position = m_position - m_camera_offeset;
}

void BlockyBalboa::updateToShader()
{
	model_matrix = cece::createTranslationMatrix(m_position);
	m_Program->updateUniform("model_matrix", model_matrix.c_arr());
	m_Program->updateUniform("mvp", m_camera->getMVP().c_arr());
}

void BlockyBalboa::moveForward()
{
	//update positions
	m_position += m_forward * g_deltaTime * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void BlockyBalboa::moveBackward()
{
	//update positions
	m_position -= m_forward * g_deltaTime * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void BlockyBalboa::moveRight()
{
	//update positions
	m_position += m_right * g_deltaTime * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void BlockyBalboa::moveLeft()
{
	//update positions
	m_position -= m_right * g_deltaTime * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void BlockyBalboa::moveUp()
{
	//update positions
	m_position += m_up * g_deltaTime * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void BlockyBalboa::moveDown()
{
	//update positions
	m_position -= m_up * g_deltaTime * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void BlockyBalboa::yawRight()
{
	m_euler_angle.y += g_deltaTime * rot_speed;
	m_euler_angle.y = fmodf(m_euler_angle.y, 360.0f);
	m_forward = m_euler_angle.ToVector();
	m_forward.y = 0;
	m_forward.normalize();
	m_right = m_forward.CrossMultiply(m_up);

	m_camera->yaw = m_euler_angle.y * 180.0f / PI + 90.0f;
	updateCameraPosition();
	updateToShader();

	printf("Euler yaw: %f, Camera yaw: %f\n", m_euler_angle.y, m_camera->yaw);
}

void BlockyBalboa::yawLeft()
{
	m_euler_angle.y -= g_deltaTime * rot_speed;
	m_euler_angle.y = fmodf(m_euler_angle.y, 360.0f);
	m_forward = m_euler_angle.ToVector();
	m_forward.y = 0;
	m_forward.normalize();
	m_right = m_forward.CrossMultiply(m_up);

	m_camera->yaw = m_euler_angle.y * 180.0f / PI + 90.0f;
	updateCameraPosition();
	updateToShader();

	printf("Euler yaw: %f, Camera yaw: %f\n", m_euler_angle.y, m_camera->yaw);
}